#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]) {
    // get semicolon separated list of files
    if (argc != 2) { return 0; }
    string list = argv[1];
    list += ';'; // add ending separator

    // locale to allow only english letters in names
    setlocale(LC_ALL, "en_US.utf-8");

    ofstream out("Shaders.hpp");
    out << "#ifndef OPENGL_SHADERS_HPP" << endl;
    out << "#define OPENGL_SHADERS_HPP" << endl;
    out << endl;
    out << "#include <vector>" << endl;
    out << "#include <GL/glew.h>" << endl;
    out << endl;
    out << "GLuint VertexShader(const GLchar[]) noexcept(false);" << endl;
    out << endl;
    out << "GLuint FragmentShader(const GLchar shader[]) noexcept(false);" << endl;
    out << endl;
    out << "GLuint ShaderProgram(const std::vector<GLuint>&) noexcept(false);" << endl;
    for (string::size_type pos = list.find(';');
         pos != string::npos;
         list.erase(0, pos + 1), pos = list.find(';')) {
        // test file exists
        const string filename = list.substr(0, pos);;
        ifstream in(filename);
        if (!in.good()) { continue; }

        // validate filename, split it into name and extension
        const string::size_type pos1 = filename.rfind('/');
        const string::size_type pos2 = filename.rfind('.');
        if (pos1 > pos2) { continue; }
        string name = filename.substr(pos1 + 1, pos2 - pos1 - 1);
        string ext = filename.substr(pos2 + 1);
        if (!all_of(name.begin(), name.end(), [](char c) {
            return isalpha(c) || isnumber(c) || c == '_';
        })) { continue; }
        else {
            transform(name.begin(), name.end(), name.begin(),
                      [](unsigned char c) { return toupper(c); }
            );
            transform(ext.begin(), ext.end(), ext.begin(),
                      [](unsigned char c) { return tolower(c); }
            );
        }

        // output
        if (ext == "frag") {
            out << endl << "const GLchar FRAG_" << name << "[] = R\"~(" << endl;
        } else if (ext == "vert") {
            out << endl << "const GLchar VERT_" << name << "[] = R\"~(" << endl;
        } else { continue; }
        out << in.rdbuf();
        out << ")~\";" << endl;

        in.close();
    }
    out << endl;
    out << "#endif //OPENGL_SHADERS_HPP" << endl;
    out.close();
    return 0;
}
