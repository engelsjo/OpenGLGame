//
//  Shader.cpp
//  Shaders
//
//  Created by Hans Dulimarta on 02/24/13.
//
//
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include "Shader.h"

Shader::Shader (const string& vs_file, const string& fs_file)
{
    prog_id = glCreateProgram();

    vs_id = load(vs_file, GL_VERTEX_SHADER);
    fs_id = load(fs_file, GL_FRAGMENT_SHADER);
    if (vs_id < 0 || fs_id < 0)
        throw "Can't load shaders file(s)";

    glAttachShader(prog_id, vs_id);
    glAttachShader(prog_id, fs_id);
    glLinkProgram(prog_id);
    GLint status;
    glGetProgramiv(prog_id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int len;
        char *log;
        glGetProgramiv (prog_id, GL_INFO_LOG_LENGTH, &len);
        log = new char[len];
        glGetProgramInfoLog(prog_id, len, &len, log);
        cerr << "Link log: " << log << endl;
        delete[] log;
        throw "Can't link shaders";
    }
}

Shader::~Shader() {
    glDetachShader(prog_id, vs_id);
    glDetachShader(prog_id, fs_id);
    glDeleteProgram(prog_id);
}

int Shader::load(const string& fname, int shader_type)
{
    int sh_id;
    ifstream sh_file (fname.c_str());
    string code;
    if (sh_file.is_open()) {
        string line;
        while (getline(sh_file, line))
        {
            code.append(line + "\n");
        }
        //cout << "Code is : " << code << endl;
        const char *code_str = code.c_str();
        sh_file.close();
        sh_id = glCreateShader(shader_type);
        glShaderSource(sh_id, 1, &code_str, NULL);
        glCompileShader(sh_id);
        int status;
        glGetShaderiv(sh_id, GL_COMPILE_STATUS, &status);
        if (!status) {
            GLint len;
            glGetShaderiv(sh_id, GL_INFO_LOG_LENGTH, &len);
            char *log = new char[len];
            glGetShaderInfoLog(sh_id, len, &len, log);
            auto pos = fname.find_last_of('/');
            if (pos != string::npos) {
                pos++;
                string bname = fname.substr(pos, fname.length() - pos);
                cerr << bname << ": " << log << endl;
            }
            else
                cerr << fname << ": " << log << endl;
            delete [] log;
            return -1;
        }
        else {
            return sh_id;
        }
    }
    else {
        cerr << "File not found: " << fname << endl;
        return -1;
    }
}
