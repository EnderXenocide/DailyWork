##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=DailyWork
ConfigurationName      :=Release
WorkspacePath          := "I:\Workspace\CodeLiteC++"
ProjectPath            := "I:\Workspace\CodeLiteC++\DailyWork"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Trinquard
Date                   :=22/09/2015
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=C:/Utils/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/Utils/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
Preprocessors          :=$(PreprocessorSwitch)__WX__ $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="DailyWork.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/Utils/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  -mwindows -s $(shell wx-config --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)I:/Workspace/CodeLiteC++/rapidjson/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/Utils/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/Utils/TDM-GCC-64/bin/g++.exe
CC       := C:/Utils/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
ASFLAGS  := 
AS       := C:/Utils/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\Utils\wxWidgets-3.0.2
WXCFG:=gcc_dll\mswu
Objects0=$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix) $(IntermediateDirectory)/gui2.cpp$(ObjectSuffix) $(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix) $(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) 



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
$(IntermediateDirectory)/gui.cpp$(ObjectSuffix): gui.cpp $(IntermediateDirectory)/gui.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/gui.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui.cpp$(DependSuffix): gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui.cpp$(DependSuffix) -MM "gui.cpp"

$(IntermediateDirectory)/gui.cpp$(PreprocessSuffix): gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui.cpp$(PreprocessSuffix) "gui.cpp"

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix): dailyworkparser.cpp $(IntermediateDirectory)/dailyworkparser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/dailyworkparser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dailyworkparser.cpp$(DependSuffix): dailyworkparser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/dailyworkparser.cpp$(DependSuffix) -MM "dailyworkparser.cpp"

$(IntermediateDirectory)/dailyworkparser.cpp$(PreprocessSuffix): dailyworkparser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dailyworkparser.cpp$(PreprocessSuffix) "dailyworkparser.cpp"

$(IntermediateDirectory)/gui2.cpp$(ObjectSuffix): gui2.cpp $(IntermediateDirectory)/gui2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/gui2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui2.cpp$(DependSuffix): gui2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui2.cpp$(DependSuffix) -MM "gui2.cpp"

$(IntermediateDirectory)/gui2.cpp$(PreprocessSuffix): gui2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui2.cpp$(PreprocessSuffix) "gui2.cpp"

$(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix): myrichtext.cpp $(IntermediateDirectory)/myrichtext.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/myrichtext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/myrichtext.cpp$(DependSuffix): myrichtext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/myrichtext.cpp$(DependSuffix) -MM "myrichtext.cpp"

$(IntermediateDirectory)/myrichtext.cpp$(PreprocessSuffix): myrichtext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/myrichtext.cpp$(PreprocessSuffix) "myrichtext.cpp"

$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "I:/Workspace/CodeLiteC++/DailyWork/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


