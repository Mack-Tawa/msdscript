//
// Created by Mack on 3/30/23.
//

#ifndef CLION_BULL_POINTER_H
#define CLION_BULL_POINTER_H

#define NEW(T) new T
# define PTR(T) T*
# define CAST(T) dynamic_cast<T*>
# define CLASS(T) class T
# define THIS this
#else
# define NEW(T) std::make_shared<T>
# define PTR(T) std::shared_ptr<T>
# define CAST(T) std::dynamic_pointer_cast<T>
# define CLASS(T) class T : public std::enable_shared_from_this<T>
# define THIS shared_from_this()

#endif //CLION_BULL_POINTER_H
