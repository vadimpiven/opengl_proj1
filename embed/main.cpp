#include <fstream>
#include <string>
#include <cctype>

using namespace std;

const char header[] = R"~(
#include <vector>
#include <GL/glew.h>

class Shader {
    GLuint program;

    static
    GLuint vertexShader(const GLchar[]) noexcept(false);

    static
    GLuint fragmentShader(const GLchar[]) noexcept(false);

    static
    GLuint shaderProgram(GLuint, GLuint) noexcept(false);

public:
    Shader() = delete;

    Shader(const Shader &) = delete;

    explicit
    Shader(const GLchar[], const GLchar[]) noexcept(false);

    void Bind() const noexcept;

    void Unbind() const noexcept;

    GLuint GetUniform(const GLchar *) const noexcept(false);

    virtual
    ~Shader() noexcept;
};
)~";

int main(int argc, char *argv[]) {
    // get semicolon separated list of files
    if (argc != 2) { return 0; }
    string list = argv[1];
    list += ';'; // add ending separator

    // locale to allow only english letters in names
    setlocale(LC_ALL, "en_US.utf-8");

    ofstream out("Shader.hpp");
    out << "#ifndef OPENGL_SHADER_HPP" << endl;
    out << "#define OPENGL_SHADER_HPP" << endl;
    out << header;
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
    out << endl << "#endif //OPENGL_SHADER_HPP" << endl;
    out.close();
    return 0;
}
