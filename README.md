# http_thread
由于历史文件过大，将http_thread项目转移到这里\
1.使用半同步/半反应堆模式，主线程作为IO单元，子线程作为逻辑单元\
2.边缘触发的epoll监视请求事件，主线程处理完IO任务后将任务放到请求队列中，工作线程通过信号量竞争进行后续处理并将结果写入buffer，处理完后通知主线程一次性发回客户端\
3.使用线程池避免了动态创建线程\
4.使用有限状态机解析http请求\
5.利用定时器释放非活跃连接（3月20日完成）\
6.连接数据库，通过数据库的增加与查找，实现登录界面的注册和登录，（4月8日完成）\
网站ip地址:http://www.jinyj.xyz/blog/login.html\
调用格式:\
./build/http_thread [-t thread_number] [-p port]
