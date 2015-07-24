##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=DailyWork
ConfigurationName      :=Debug
WorkspacePath          := "I:\Workspace\CodeLiteC++"
ProjectPath            := "I:\Workspace\CodeLiteC++\DailyWork"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Trinquard
Date                   :=24/07/2015
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
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="DailyWork.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/Utils/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  -mwindows $(shell wx-config --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). 
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
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
ASFLAGS  := 
AS       := C:/Utils/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\Utils\wxWidgets-3.0.2
WXCFG:=gcc_dll\mswu
Objects0=$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/DailyWorkParser.cpp$(ObjectSuffix) $(IntermediateDirectory)/gason.cpp$(ObjectSuffix) $(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

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

$(IntermediateDirectory)/DailyWorkParser.cpp$(ObjectSuffix): DailyWorkParser.cpp $(IntermediateDirectory)/DailyWorkParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/DailyWorkParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DailyWorkParser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DailyWorkParser.cpp$(DependSuffix): DailyWorkParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DailyWorkParser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DailyWorkParser.cpp$(DependSuffix) -MM "DailyWorkParser.cpp"

$(IntermediateDirectory)/DailyWorkParser.cpp$(PreprocessSuffix): DailyWorkParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DailyWorkParser.cpp$(PreprocessSuffix) "DailyWorkParser.cpp"

$(IntermediateDirectory)/gason.cpp$(ObjectSuffix): gason.cpp $(IntermediateDirectory)/gason.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/gason.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gason.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gason.cpp$(DependSuffix): gason.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gason.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gason.cpp$(DependSuffix) -MM "gason.cpp"

$(IntermediateDirectory)/gason.cpp$(PreprocessSuffix): gason.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gason.cpp$(PreprocessSuffix) "gason.cpp"

$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "I:/Workspace/CodeLiteC++/DailyWork/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


