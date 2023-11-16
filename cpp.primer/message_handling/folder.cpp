#include "folder.h"
#include "message.h"

Folder::Folder():
name("NonNameFolder") {

}

Folder::Folder(const string& name_):
name(name_) {

}

Folder::~Folder() {
    while (!messages.empty()) {
        (*messages.begin())->remove(*this);
    }
}

void Folder::add_msg(Message * msg) {
    messages.insert(msg);
}

void Folder::rm_msg(Message * msg) {
    messages.erase(msg);
}