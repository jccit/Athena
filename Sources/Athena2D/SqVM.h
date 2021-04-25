#pragma once

#include <simplesquirrel/simplesquirrel.hpp>

class SqVM {
public:
    static SqVM& getInstance();
    ~SqVM();

    void shutdown();

    void exec(std::string script);
    void runScript(std::string path);

    static ssq::Function* findFunc(ssq::Class& cls, const std::string& name);

    ssq::VM* vm;

    template <class... Args>
    bool callFunc(std::string name, ssq::Instance* instance, ssq::Function* func, Args... args)
    {
        if (instance != nullptr && func != nullptr) {
            try {
                getInstance().vm->callFunc(*func, *instance, args...);
            } catch (ssq::RuntimeException& e) {
                LOG_ERROR(e.what(), name);
                return false;
            } catch (ssq::TypeException& e) {
                LOG_ERROR(e.what(), name);
                return false;
            }
        }

        return true;
    }

private:
    SqVM();
};
