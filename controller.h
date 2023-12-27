#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "model.h"
#include "view.h"
#include "callable.h"


class Controller :public Callable
{
public:
        Controller(Model& model, View& view)
        {
                this->set_model(model);
                this->set_view(view);
        }

        void set_model(Model& model)
        {
                this->model = &model;
                this->model->register_data_changed_handler(this);
        }

        void set_view(View& view)
        {
                this->view = &view;
        }

        void notify() override
        {
                auto str = this->model->data();

                if (this->view != nullptr)
                        this->view->set_data(str);
        }
private:

        Model* model{ nullptr };

        View* view{ nullptr };
};


#endif // CONTROLLER_H

