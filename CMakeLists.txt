cmake_minimum_required(VERSION 3.29.6)
project(AllExamFiles C)

set(CMAKE_C_STANDARD 11)

# 仅递归扫描src目录下的.c文件
file(GLOB_RECURSE SOURCE_FILES "src/*.c")

# 为每个.c文件创建独立可执行文件
foreach(SRC_FILE ${SOURCE_FILES})
    # 提取文件名（含相对路径）
    get_filename_component(FILE_NAME ${SRC_FILE} NAME_WE)

    # 创建可执行文件目标
    add_executable(${FILE_NAME} ${SRC_FILE})

    # 添加编译选项（如需跨平台兼容）
    target_compile_options(${FILE_NAME} PRIVATE
            -Wall -Wextra -pedantic
    )
endforeach()

# 可选：添加统一的编译选项
#add_compile_options(-Wall -Wextra -pedantic)


#每次新增 C 文件后，
#右键点击项目根目录 -> Reload CMake Project，
#CLion 会重新解析配置，生成对应的运行目标。
#在右上角运行配置下拉菜单中，选择要运行的 C 文件对应的可执行目标

#彻底理解代码逻辑后独立实现 核心原则：避免直接复制粘贴他人代码。通过深入理解算法或功能的逻辑后，用自己的思路重新实现。 示例：如果参考了排序算法，尝试改用不同的实现方式（如将递归改为迭代，或调整循环结构）。
#重构代码结构 变量/函数重命名：使用有意义的自定义名称替换通用命名（如将 temp 改为 currentValue）。 调整代码顺序：在不影响逻辑的前提下，重新组织函数、条件判断或循环的顺序。 拆分或合并函数：将长函数拆分为多个子函数，或将重复代码合并为通用模块。
#采用不同的算法或数据结构 替换等价方法：例如，用快速排序替代冒泡排序，或用哈希表替代数组遍历查找。 调整实现细节：例如，在实现相同功能时选择不同的循环结构（for vs while）或条件判断方式。
#增加代码个性化 添加注释与文档：通过详细的注释解释代码逻辑，展示个人思考过程。 自定义工具函数：封装一些辅助函数（如日志输出、数据验证），体现个人编码风格。 代码格式化差异：调整缩进、空格或换行风格（需符合语言规范）。
#避免使用模板或通用代码 简化冗余代码：删除与功能无关的模板代码（如未使用的变量或重复注释）。请通过以上方法合理降低代码查重率和相似性。
