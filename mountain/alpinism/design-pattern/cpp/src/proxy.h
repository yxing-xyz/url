/*
是什么:
    代理模式是一种结构型设计模式， 让你能够提供对象的替代品或其占位符。 代理控制着对于原对象的访问， 并允许在将请求提交给对象前后进行一些处理。

为什么:
    为什么要控制对于某个对象的访问呢？ 举个例子： 有这样一个消耗大量系统资源的巨型对象， 你只是偶尔需要使用它， 并非总是需要。
    你可以实现延迟初始化： 在实际有需要时再创建该对象。 对象的所有客户端都要执行延迟初始代码。 不幸的是， 这很可能会带来很多重复代码。
    在理想情况下， 我们希望将代码直接放入对象的类中， 但这并非总是能实现： 比如类可能是第三方封闭库的一部分。
    应用场景:
    1. 延迟初始化（虚拟代理）。 如果你有一个偶尔使用的重量级服务对象， 一直保持该对象运行会消耗系统资源时， 可使用代理模式。
    2. 访问控制（保护代理）。 如果你只希望特定客户端使用服务对象， 这里的对象可以是操作系统中非常重要的部分， 而客户端则是各种已启动的程序 （包括恶意程序）， 此时可使用代理模式。
    3. 本地执行远程服务 （远程代理）。 适用于服务对象位于远程服务器上的情形。
    4. 记录日志请求 （日志记录代理）。 适用于当你需要保存对于服务对象的请求历史记录时。 代理可以在向服务传递请求前进行记录。

怎么做:
    1. 如果没有现成的服务接口， 你就需要创建一个接口来实现代理和服务对象的可交换性。 从服务类中抽取接口并非总是可行的， 因为你需要对服务的所有客户端进行修改， 让它们使用接口。 备选计划是将代理作为服务类的子类， 这样代理就能继承服务的所有接口了。
    2. 创建代理类， 其中必须包含一个存储指向服务的引用的成员变量。 通常情况下， 代理负责创建服务并对其整个生命周期进行管理。 在一些特殊情况下， 客户端会通过构造函数将服务传递给代理。
    3. 根据需求实现代理方法。 在大部分情况下， 代理在完成一些任务后应将工作委派给服务对象。
    4. 可以考虑新建一个构建方法来判断客户端可获取的是代理还是实际服务。 你可以在代理类中创建一个简单的静态方法， 也可以创建一个完整的工厂方法。
    5. 可以考虑为服务对象实现延迟初始化。


心得:
装饰和代理有着相似的结构， 但是其意图却非常不同。 这两个模式的构建都基于组合原则， 也就是说一个对象应该将部分工作委派给另一个对象。 两者之间的不同之处在于代理通常自行管理其服务对象的生命周期， 而装饰的生成则总是由客户端进行控制。 这里的代码对象也是客户端传递进去的感觉边界很模糊,也可以不传递初始化列表延迟创建 只是代理类固定了代理的实际对象, 如果换成接口, 感觉也是动态代理不同对象
*/
#ifndef DESIGN_PATTERNS_PROXY_H
#define DESIGN_PATTERNS_PROXY_H
namespace proxy
{
    class Subject
    {
    public:
        virtual void Request() const = 0;
    };

    class RealSubject : public Subject
    {
    public:
        void Request() const override;
    };

    class Proxy : public Subject
    {
    private:
        RealSubject *real_subject_;
        bool CheckAccess() const;
        void LogAccess() const;

    public:
        Proxy(RealSubject *);
        ~Proxy();
        void Request() const override;
    };

    void ClientCode(const Subject &);
    void run();
}
#endif //DESIGN_PATTERNS_PROXY_H