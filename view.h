#ifndef VIEW_H
#define VIEW_H


#include <iostream>
#include <string>

class View
{

public:
        void set_data(const std::string& value) const
        {
                std::cout << "display string:  " << value << std::endl;
        }
};



#endif // VIEW_H