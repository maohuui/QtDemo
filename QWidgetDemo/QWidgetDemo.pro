TEMPLATE = subdirs
#定义了ordered表示子项目按照添加的顺序来编译
CONFIG  += ordered
SUBDIRS += 01-lightbutton \    #高亮按钮控件
        02-movewidget \          #通用控件移动类
        03-flatui \
        04-countcode

##
#多工程
    #如果需要管理多工程（pro），比如：库工程、界面工程，其中，每一个工程均可单独编译成功，但存在依赖关系。也就是说，lib2依赖于lib1，而UI依赖于lib2。
    #配置如下：
        #配置TEMPLATE为subdirs设置多工程
        #配置SUBDIRS，指定需要添加的工程模块
        #配置CONFIG为ordered指定顺序编译

#多模块
    #延续多工程，如果某一个工程功能比较多，我们必然要进行模块化。例如：界面工程包含：登录界面、设置界面、主界面。。。这时，我们就可以使用pri模块化了
