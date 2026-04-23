class Base
{
    public:
//короче паттерн стратегия
    template<typename Type>
    virtual  void getValue(Type &value) = 0;
};