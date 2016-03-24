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
Date                   :=21/03/2016
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
Preprocessors          :=$(PreprocessorSwitch)__WX__ $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="DailyWork.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/windres.exe
LinkOptions            :=  -mwindows -s $(shell wx-config --debug=no  --libs std,stc --unicode=yes)
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
AR       := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/ar.exe rcu
CXX      := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/g++.exe
CC       := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall -std=gnu++14 $(shell wx-config --cxxflags --unicode=yes --debug=no --libs std stc) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no --libs std stc) $(Preprocessors)
ASFLAGS  := 
AS       := C:/Utils/mingw-w64/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\utils\wxWidgets
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix) $(IntermediateDirectory)/gui2.cpp$(ObjectSuffix) $(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix) $(IntermediateDirectory)/prefs.cpp$(ObjectSuffix) $(IntermediateDirectory)/mystyledtext.cpp$(ObjectSuffix) $(IntermediateDirectory)/excludeddays.cpp$(ObjectSuffix) $(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix): dailyworkparser.cpp $(IntermediateDirectory)/dailyworkparser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/dailyworkparser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dailyworkparser.cpp$(DependSuffix): dailyworkparser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dailyworkparser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/dailyworkparser.cpp$(DependSuffix) -MM "dailyworkparser.cpp"

$(IntermediateDirectory)/dailyworkparser.cpp$(PreprocessSuffix): dailyworkparser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dailyworkparser.cpp$(PreprocessSuffix) "dailyworkparser.cpp"

$(IntermediateDirectory)/gui2.cpp$(ObjectSuffix): gui2.cpp $(IntermediateDirectory)/gui2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/gui2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui2.cpp$(DependSuffix): gui2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui2.cpp$(DependSuffix) -MM "gui2.cpp"

$(IntermediateDirectory)/gui2.cpp$(PreprocessSuffix): gui2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui2.cpp$(PreprocessSuffix) "gui2.cpp"

$(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix): myrichtext.cpp $(IntermediateDirectory)/myrichtext.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/myrichtext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/myrichtext.cpp$(DependSuffix): myrichtext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/myrichtext.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/myrichtext.cpp$(DependSuffix) -MM "myrichtext.cpp"

$(IntermediateDirectory)/myrichtext.cpp$(PreprocessSuffix): myrichtext.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/myrichtext.cpp$(PreprocessSuffix) "myrichtext.cpp"

$(IntermediateDirectory)/prefs.cpp$(ObjectSuffix): prefs.cpp $(IntermediateDirectory)/prefs.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/prefs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/prefs.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/prefs.cpp$(DependSuffix): prefs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/prefs.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/prefs.cpp$(DependSuffix) -MM "prefs.cpp"

$(IntermediateDirectory)/prefs.cpp$(PreprocessSuffix): prefs.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/prefs.cpp$(PreprocessSuffix) "prefs.cpp"

$(IntermediateDirectory)/mystyledtext.cpp$(ObjectSuffix): mystyledtext.cpp $(IntermediateDirectory)/mystyledtext.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/mystyledtext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mystyledtext.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mystyledtext.cpp$(DependSuffix): mystyledtext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mystyledtext.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/mystyledtext.cpp$(DependSuffix) -MM "mystyledtext.cpp"

$(IntermediateDirectory)/mystyledtext.cpp$(PreprocessSuffix): mystyledtext.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mystyledtext.cpp$(PreprocessSuffix) "mystyledtext.cpp"

$(IntermediateDirectory)/excludeddays.cpp$(ObjectSuffix): excludeddays.cpp $(IntermediateDirectory)/excludeddays.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "I:/Workspace/CodeLiteC++/DailyWork/excludeddays.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/excludeddays.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/excludeddays.cpp$(DependSuffix): excludeddays.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/excludeddays.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/excludeddays.cpp$(DependSuffix) -MM "excludeddays.cpp"

$(IntermediateDirectory)/excludeddays.cpp$(PreprocessSuffix): excludeddays.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/excludeddays.cpp$(PreprocessSuffix) "excludeddays.cpp"

$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "I:/Workspace/CodeLiteC++/DailyWork/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


