//
//  Shader.h
//  Shaders
//
//  Created by Hans Dulimarta on 02/24/13.
//
//

#ifndef __Shaders__Shader__
#define __Shaders__Shader__

#include <string>
using namespace std;
class Shader {
public:
    Shader (const string& vs_file, const string& fs_file);
    ~Shader();
    int id() const { return prog_id; }
    void use() const {
        glUseProgram(prog_id);
    }
private:
    int load (const string& file_name, int shader_type);
    int prog_id;
    int vs_id, fs_id;
};
#endif /* defined(__Shaders__Shader__) */
