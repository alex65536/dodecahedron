#ifndef ABOUT_H_INCLUDED
#define ABOUT_H_INCLUDED

#ifdef NO_USE_EXTERN
    const char* app_name = "Dodecahedron";
    const char* app_version = "0.0.1.2-pre-alpha";
    const char* app_author = "Kernozhitsky Alexander (alex256)";
#else
    extern const char* app_name;
    extern const char* app_version;
    extern const char* app_author;
#endif

void hello_message();
void show_uci_about();

#endif // ABOUT_H_INCLUDED
