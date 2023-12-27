#ifndef MODEL_H
#define MODEL_H


#include "callable.h"

class Model
{
public:

        std::string data() const
        {
                return this->m_data;
        }

        void set_data(const std::string& data)
        {
                this->m_data = data;

                if (this->event != nullptr)
                {
                        this->event->notify();
                }
        }

        void register_data_changed_handler(Callable* controller)
        {
                this->event = controller;
        }
private:
        std::string m_data;
        Callable* event{ nullptr };
};



#endif // MODEL_H
