
cc        := g++
name      := pro
workdir   := workspace
srcdir    := src
objdir    := objs
stdcpp    := c++11
cuda_home := /home/xd2/.local/lib/python3.6/site-packages/trtpy/trt8cuda102cudnn8
syslib    := /home/xd2/.local/lib/python3.6/site-packages/trtpy/lib
# cpp_pkg   := /home/xd2/.local/lib/python3.6/site-packages/trtpy/cpp-packages
cpp_pkg   := /home/zwl/software
cuda_arch := 
nvcc      := $(cuda_home)/bin/nvcc -ccbin=$(cc)
python_path :=/home/xd2/anaconda3/envs/paddle_ocr

cpp_srcs := $(shell find src -name "*.cpp") # 查找src目录下所有.cpp文件，包括在src各级子目录下的cpp文件，返回内容示例：src/1.cpp src/http/2.cpp src/3.cpp
cpp_objs := $(cpp_srcs:.cpp=.o)				# 将cpp_srcs中的.cpp后缀改为.o后缀，返回内容示例:src/1.o src/2.o src/3.o
cpp_objs := $(cpp_objs:src/%=objs/%)		# 将src/改为objs
cpp_mk   := $(cpp_objs:.o=.mk)				# makefile (mk)文件

c_srcs := $(shell find src -name "*.c")
c_objs := $(c_srcs:.c=.co)
c_objs := $(c_objs:src/%=objs/%)
c_mk   := $(c_objs:.co=.cmk)

cu_srcs := $(shell find src -name "*.cu")
cu_objs := $(cu_srcs:.cu=.cuo)
cu_objs := $(cu_objs:src/%=objs/%)
cu_mk   := $(cu_objs:.cuo=.cumk)\



# 配置你的库路径
# 1. cudnn8.2.2.26（请自行下载）
#    runtime的tar包，runtime中包含了lib、so文件
#    develop的tar包，develop中包含了include、h等文件
# 2. tensorRT-8.0.1.6-cuda10.2（请自行下载）
#    tensorRT下载GA版本（通用版、稳定版），EA（尝鲜版本）不要
# 3. cuda10.2，也可以是11.x看搭配（请自行下载安装）

# lean_tensor_rt := /data/sxai/lean/TensorRT-8.0.1.6-cuda10.2-cudnn8.2
# lean_cudnn     := /data/sxai/lean/cudnn8.2.2.26
# lean_opencv    := /data/sxai/lean/opencv4.2.0
# lean_cuda      := /data/sxai/lean/cuda-10.2

# lean_tensor_rt := /data/sxai/lean/TensorRT-7.0.0.11
# lean_cudnn     := /data/sxai/lean/cudnn7.6.5.32-cuda10.2
# lean_opencv    := /data/sxai/lean/opencv4.2.0
# lean_cuda      := /data/sxai/lean/cuda-10.2

# lean_tensor_rt := /data/sxai/lean/TensorRT-7.2.1.6
# lean_cudnn     := /data/sxai/lean/cudnn8.2.2.26
# lean_opencv    := /data/sxai/lean/opencv4.2.0
# lean_cuda      := /data/sxai/lean/cuda-11.1

# link_cuda      := cudart cudnn
# link_trtpro    := 
# link_tensorRT  := nvinfer nvinfer_plugin
# link_opencv    := opencv_core opencv_imgproc opencv_imgcodecs opencv_videoio
# link_sys       := stdc++ dl protobuf
# link_librarys  := $(link_cuda) $(link_tensorRT) $(link_sys) $(link_opencv)


include_paths := src              \
	src/tensorRT                  \
    $(cuda_home)/include/cuda     \
	$(cuda_home)/include/tensorRT \
	$(cpp_pkg)/opencv4.2/include/opencv4  \
	$(cuda_home)/include/protobuf \
	$(python_path)/include/python3.9

library_paths := $(cuda_home)/lib64 $(syslib) $(cpp_pkg)/opencv4.2/lib /usr/lib/x86_64-linux-gnu/ $(python_path)/lib


link_librarys := opencv_core opencv_imgproc opencv_videoio  opencv_imgcodecs opencv_highgui \
			nvinfer nvonnxparser \
			cuda cublas cudart cudnn \
			stdc++ dl python3.9


paths     := $(foreach item,$(library_paths),-Wl,-rpath=$(item)) # 循环将$(library_paths)中的单词取出来放进item，然后执行表达式-Wl,-rpath=$(item)
																 # 返回的结果为-Wl,-rpath=item1 -Wl,-rpath=item2 -Wl,-rpath=item3等
																 # -Wl,-rpath=指定运行时链接到的库
include_paths := $(foreach item,$(include_paths),-I$(item))		 # 编译程序按照-I指定的路径进去搜索头文件
library_paths := $(foreach item,$(library_paths),-L$(item))		 # -L指定的路径会被优先搜索
link_librarys := $(foreach item,$(link_librarys),-l$(item))		 # -L用于指定库所在的目录，-l用于指定具体的库

# 如果是其他显卡，请修改-gencode=arch=compute_75,code=sm_75为对应显卡的能力
# 显卡对应的号码参考这里：https://developer.nvidia.com/zh-cn/cuda-gpus#compute
# 如果是 jetson nano，提示找不到-m64指令，请删掉 -m64选项。不影响结果
cpp_compile_flags := -std=c++11 -fPIC -m64 -g -fopenmp -w -O0		# C++语言也经历了很多的标准变化，例如C++11，C++14，这里通过-std选择C++11标准进行编译
																	# -fPIC生成位置无关目标代码，适用于动态连接；
cu_compile_flags  := -std=c++11 -m64 -Xcompiler -fPIC -g -w -gencode=arch=compute_75,code=sm_75 -O0
link_flags        := -pthread -fopenmp -Wl,-rpath='$$ORIGIN' 

cpp_compile_flags += $(include_paths) 	# +=用于添加单词
cu_compile_flags  += $(include_paths)
link_flags 		  += $(library_paths) $(link_librarys) $(paths) 

ifneq ($(MAKECMDGOALS), clean) # make clean时，不起作用
-include $(cpp_mk) $(cu_mk) $(c_mk) # 忽略当前此行命令执行时候所遇到的错误。比如删除一个不存在的文件等，那么也不要管，继续执行make。
endif

pro    : workspace/pro
workspace/pro : $(c_objs) $(cpp_objs) $(cu_objs)
	@echo Link $@
	@mkdir -p $(dir $@)
	@g++ $^ -o $@ $(link_flags) 

objs/%.o : src/%.cpp
	@echo Compile CXX $<
	@mkdir -p $(dir $@)
	@g++ -c $< -o $@ $(cpp_compile_flags) $(link_flags)

objs/%.co : src/%.c
	@echo Compile C $<
	@mkdir -p $(dir $@)
	@g++ -c $< -o $@ $(cpp_compile_flags)

objs/%.cuo : src/%.cu
	@echo Compile CUDA $<
	@mkdir -p $(dir $@)
	@nvcc -c $< -o $@ $(cu_compile_flags)

objs/%.mk : src/%.cpp
	@echo Compile depends CXX $<
	@mkdir -p $(dir $@)
	@g++ -M $< -MF $@ -MT $(@:.mk=.o) $(cpp_compile_flags)

objs/%.cmk : src/%.c
	@echo Compile depends C $<
	@mkdir -p $(dir $@)
	@g++ -M $< -MF $@ -MT $(@:.cmk=.o) $(cpp_compile_flags)
	
objs/%.cumk : src/%.cu
	@echo Compile depends CUDA $<
	@mkdir -p $(dir $@)
	@nvcc -M $< -MF $@ -MT $(@:.cumk=.cuo) $(cu_compile_flags)

run : workspace/pro
	@cd workspace && ./pro

debug :
	@echo $(includes)

clean :
	@rm -rf objs workspace/pro build

.PHONY : clean run debug
