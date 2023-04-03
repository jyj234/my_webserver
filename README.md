# http_thread
由于历史文件过大，将http_thread项目转移到这里\
1.使用半同步/半反应堆模式，主线程作为IO单元，子线程作为逻辑单元\
2.边缘触发的epoll监视请求事件，主线程处理完IO任务后将任务放到请求队列中，工作线程通过信号量竞争进行后续处理并将结果写入buffer，处理完后通知主线程一次性发回客户端\
3.使用线程池避免了动态创建线程\
4.使用有限状态机解析http请求\
5.利用定时器释放非活跃连接（3/20完成）\
6.连接数据库，记录账户信息（4/2完成）\
正在做：\
完善登录业务功能\
网站ip地址：121.41.46.247/blog/login.html（域名正在备案）\
调用格式:\
./build/http_thread [-t thread_number] [-p port]
