##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=DailyWork
ConfigurationName      :=Release
WorkspacePath          :=I:/Workspace/CodeLiteC++
ProjectPath            :=I:/Workspace/CodeLiteC++/DailyWork
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Laurent
Date                   :=19/05/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG $(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="DailyWork.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/windres.exe
LinkOptions            :=  -mwindows -s $(shell wx-config --debug=no --libs std,stc --unicode=yes)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../rapidjson/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/ar.exe rcu
CXX      := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/g++.exe
CC       := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/gcc.exe
CXXFLAGS :=  -O2 -std=gnu++14 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
ASFLAGS  := 
AS       := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\utils\wxWidgets
Objects0=$(IntermediateDirectory)/src_dailyworkparser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_excludeddays.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_gui2.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_myrichtext.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_mystyledtext.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_prefs.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_gui.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_win_resources.rc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_dailyworkparser.cpp$(ObjectSuffix): src/dailyworkparser.cpp $(IntermediateDirectory)/src_dailyworkparser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/dailyworkparser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_dailyworkparser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_dailyworkparser.cpp$(DependSuffix): src/dailyworkparser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_dailyworkparser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_dailyworkparser.cpp$(DependSuffix) -MM "src/dailyworkparser.cpp"

$(IntermediateDirectory)/src_dailyworkparser.cpp$(PreprocessSuffix): src/dailyworkparser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_dailyworkparser.cpp$(PreprocessSuffix) "src/dailyworkparser.cpp"

$(IntermediateDirectory)/src_excludeddays.cpp$(ObjectSuffix): src/excludeddays.cpp $(IntermediateDirectory)/src_excludeddays.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/excludeddays.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_excludeddays.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_excludeddays.cpp$(DependSuffix): src/excludeddays.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_excludeddays.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_excludeddays.cpp$(DependSuffix) -MM "src/excludeddays.cpp"

$(IntermediateDirectory)/src_excludeddays.cpp$(PreprocessSuffix): src/excludeddays.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_excludeddays.cpp$(PreprocessSuffix) "src/excludeddays.cpp"

$(IntermediateDirectory)/src_gui2.cpp$(ObjectSuffix): src/gui2.cpp $(IntermediateDirectory)/src_gui2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/gui2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_gui2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_gui2.cpp$(DependSuffix): src/gui2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_gui2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_gui2.cpp$(DependSuffix) -MM "src/gui2.cpp"

$(IntermediateDirectory)/src_gui2.cpp$(PreprocessSuffix): src/gui2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_gui2.cpp$(PreprocessSuffix) "src/gui2.cpp"

$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM "src/main.cpp"

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) "src/main.cpp"

$(IntermediateDirectory)/src_myrichtext.cpp$(ObjectSuffix): src/myrichtext.cpp $(IntermediateDirectory)/src_myrichtext.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/myrichtext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_myrichtext.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_myrichtext.cpp$(DependSuffix): src/myrichtext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_myrichtext.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_myrichtext.cpp$(DependSuffix) -MM "src/myrichtext.cpp"

$(IntermediateDirectory)/src_myrichtext.cpp$(PreprocessSuffix): src/myrichtext.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_myrichtext.cpp$(PreprocessSuffix) "src/myrichtext.cpp"

$(IntermediateDirectory)/src_mystyledtext.cpp$(ObjectSuffix): src/mystyledtext.cpp $(IntermediateDirectory)/src_mystyledtext.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/mystyledtext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_mystyledtext.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_mystyledtext.cpp$(DependSuffix): src/mystyledtext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_mystyledtext.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_mystyledtext.cpp$(DependSuffix) -MM "src/mystyledtext.cpp"

$(IntermediateDirectory)/src_mystyledtext.cpp$(PreprocessSuffix): src/mystyledtext.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_mystyledtext.cpp$(PreprocessSuffix) "src/mystyledtext.cpp"

$(IntermediateDirectory)/src_prefs.cpp$(ObjectSuffix): src/prefs.cpp $(IntermediateDirectory)/src_prefs.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/prefs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_prefs.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_prefs.cpp$(DependSuffix): src/prefs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_prefs.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_prefs.cpp$(DependSuffix) -MM "src/prefs.cpp"

$(IntermediateDirectory)/src_prefs.cpp$(PreprocessSuffix): src/prefs.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_prefs.cpp$(PreprocessSuffix) "src/prefs.cpp"

$(IntermediateDirectory)/src_gui.cpp$(ObjectSuffix): src/gui.cpp $(IntermediateDirectory)/src_gui.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/src/gui.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_gui.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_gui.cpp$(DependSuffix): src/gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_gui.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_gui.cpp$(DependSuffix) -MM "src/gui.cpp"

$(IntermediateDirectory)/src_gui.cpp$(PreprocessSuffix): src/gui.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_gui.cpp$(PreprocessSuffix) "src/gui.cpp"

$(IntermediateDirectory)/src_win_resources.rc$(ObjectSuffix): src/win_resources.rc
	$(RcCompilerName) -i "I:/Workspace/CodeLiteC++/DailyWork/src/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/src_win_resources.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


