## Pro文件配置

### 1.注释
从`#`开始，到这行结束

### 2.TEMPLATE
模板变量告诉qmake为这个应用程序生成哪种makefile。

|  选项    | 说明  |
|  ----   | ----  |
| app     | 创建一个用于构建应用程序的Makefile（默认）。 |
| lib     | 创建一个用于构建库的Makefile。 |
| subdirs | 创建一个用于构建目标子目录的Makefile，子目录使用SUBDIRS变量指定。 |
| aux     | 创建一个不建任何东西的Makefile。如果没有编译器需要被调用来创建目标，比如你的项目使用解释型语言写的，使用此功能。注：此模板类型只能用于Makefile-based生成器。特别是，它不会工作在vcxproj和Xcode生成器。 |
| vcapp   | 仅适用于Windows。创建一个Visual Studio应用程序项目。 |
| vclib   | 仅适用于Windows。创建一个Visual Studio库项目。 |

### 3.CONFIG
指定编译器选项和项目配置，值由qmake内部识别并具有特殊意义。
以下配置值控制编译标志
|  选项    | 说明  |
|  ----   | ----  |
|  release   |项目以release模式构建。如果也指定了debug，那么最后一个生效。
|  debug   |项目以debug模式构建。
|  debug_and_release   |项目准备以debug和release两种模式构建。
|  debug_and_release_target   |此选项默认设置。如果也指定了debug_and_release，最终的debug|  和release构建在不同的目录。
|  build_all   |如果指定了debug_and_release，默认情况下，该项目会构建为debug和release模式。
|  autogen_precompile_source   |自动生成一个.cpp文件，包含在.pro中指定的预编译头文件。
|  ordered   |使用subdirs模板时，此选项指定应该按照目录列表的顺序处理它们。
|  precompile_header   |可以在项目中使用预编译头文件的支持。
|  warn_on   |编译器应该输出尽可能多的警告。如果也指定了warn_off，最后一个生效。
|  warn_off   |编译器应该输出尽可能少的警告。
|  exceptions   |启用异常支持。默认设置。
|  exceptions_off   |禁用异常支持。
|  rtti   |启用RTTI支持。默认情况下，使用编译器默认。
|  rtti_off   |禁用RTTI支持。默认情况下，使用编译器默认。
|  stl   |启用STL支持。默认情况下，使用编译器默认。
|  stl_off   |禁用STL支持。默认情况下，使用编译器默认。
|  thread   |启用线程支持。当CONFIG包括qt时启用，这是缺省设置。
|  c++11   |启用c++11支持。如果编译器不支持c++11这个选项，没有影响。默认情况下，支持是禁用的。
|  c++14   |启用c++14支持。如果编译器不支持c++14这个选项，没有影响。默认情况下，支持是禁用的。

### 4.DEFINES
qmake添加这个变量的值作为编译器C预处理器宏(-D选项)。

### 5.INCLUDEPATH
指定编译项目时应该被搜索的#include目录。

### 6.DEPENDPATH
指定程序编译时依赖的相关路径。

### 7.DESTDIR
指定在何处放置目标文件。

### 8.TARGET
指定目标文件的名称。默认情况下包含的项目文件的基本名称。

### 9.OUT_PWD
指定构建目录。

### 10.MOC_DIR
指定来自moc的所有中间文件放置的目录（含Q_OBJECT宏的头文件转换成标准.h文件的存放目录）。

### 11.OBJECTS_DIR
指定所有中间文件.o（.obj）放置的目录。

### 12.RCC_DIR
指定Qt资源编译器输出文件的目录（.qrc文件转换成qrc_*.h文件的存放目录）。

### 13.LIBS
指定链接到项目中的库列表。-L后是库文件的目录，-l后是具体的库的名字(后缀不用加)。例如：
LIBS += -L$$PWD/../../../ThirdLib/winapi -lWSock32

### 14.RC_ICONS
仅适用于Windows，指定的图标应该包含在一个生成的.rc文件里。如果RC_FILE 和RES_FILE变量都没有设置这才可利用。

### 15.TRANSLATIONS
指定包含用户界面翻译文本的翻译(.ts)文件列表。

### 16.平台相关性处理
为Windows平台加的依赖平台的文件的简单的作用域看起来就像这样：
win32 { SOURCES += hello_win.cpp }

**子项目pro文件: 每次添加一个子项目就会在SUBDIRS项目加上一个项目名，子目录项目的TEMPLATE = subdirs。CONFIG += ordered是让项目按照顺序编译，由于主程序依赖于对应的库，一般都是把MainApp放在SUBDIRS的最后.**

### 17.pri文件

对于一些库和主程序都需要的目录设置 (构建目录、obj生成目录、moc文件生成目录等)，可以统一写在一个pri文件中：

```c++
CONFIG(release, debug|release) {
    BuildType=release
    CONFIG += warn_off
} else {
    BuildType=debug
    DEFINES += __DEBUG
}

INTERMEDIATE_DIR = $$PWD/../Intermediate/$$BuildType

DESTDIR         = $$PWD/../RunImage/$$BuildType
OUT_PWD         = $$INTERMEDIATE_DIR/$$TARGET
MOC_DIR         = $$INTERMEDIATE_DIR/$$TARGET
OBJECTS_DIR     = $$INTERMEDIATE_DIR/$$TARGET
RCC_DIR         = $$INTERMEDIATE_DIR/$$TARGET
UI_DIR          = $$INTERMEDIATE_DIR/$$TARGET
```
在需要引用的pro文件中：
```c++
    include($$PWD/../../../Path.pri)
```

### 18.查看变量信息
message($$INCLUDEPATH) , 会在概要信息中打印相关变量的值


### 主程序pro文件

主程序的TEMPLATE = app。除了常规的pro设置外，要记得将自己编的库的头文件目录加上，并将生成的dll通过LIBS链接：

主程序的TEMPLATE = app。除了常规的pro设置外，要记得将自己编的库的头文件目录加上，并将生成的dll通过LIBS链接：
```c++
#library
INCLUDEPATH += \
    $$PWD/../../Libraries \

LIBS += \
    -L$$DESTDIR -lComponent -lcommonLibs \
```
### 库pro文件
库的TEMPLATE = lib。库在通过Creator新建的时候会生成一个xxx_global.h，定义了导出库的相关信息：
```c++
#include <QtCore/qglobal.h>

#if defined(TESTLIB_LIBRARY)
#  define TESTLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TESTLIBSHARED_EXPORT Q_DECL_IMPORT
#endif
```
在库中要作为接口的类记得加上对应的宏：

```c++
class TESTLIBSHARED_EXPORT TestLib : public QObject
```