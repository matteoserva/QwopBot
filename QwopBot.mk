##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=QwopBot
ConfigurationName      :=Debug
WorkspacePath          := "/home/matteo/Progetti"
ProjectPath            := "/home/matteo/Progetti/QwopBot"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=matteo
Date                   :=11/30/14
CodeLitePath           :="/home/matteo/.codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="QwopBot.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  `pkg-config --libs opencv`
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)X11 $(LibrarySwitch)xdo 
ArLibs                 :=  "X11" "xdo" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/ScreenGrabber.cpp$(ObjectSuffix) $(IntermediateDirectory)/ImageAnalyzer.cpp$(ObjectSuffix) $(IntermediateDirectory)/QwopAnalyzer.cpp$(ObjectSuffix) $(IntermediateDirectory)/KeyPresser.cpp$(ObjectSuffix) $(IntermediateDirectory)/QwopBot.cpp$(ObjectSuffix) $(IntermediateDirectory)/DecisionMaker.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:
	@echo Executing Pre Build commands ...
	echo ciao
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/ScreenGrabber.cpp$(ObjectSuffix): ScreenGrabber.cpp $(IntermediateDirectory)/ScreenGrabber.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/ScreenGrabber.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ScreenGrabber.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ScreenGrabber.cpp$(DependSuffix): ScreenGrabber.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ScreenGrabber.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ScreenGrabber.cpp$(DependSuffix) -MM "ScreenGrabber.cpp"

$(IntermediateDirectory)/ScreenGrabber.cpp$(PreprocessSuffix): ScreenGrabber.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ScreenGrabber.cpp$(PreprocessSuffix) "ScreenGrabber.cpp"

$(IntermediateDirectory)/ImageAnalyzer.cpp$(ObjectSuffix): ImageAnalyzer.cpp $(IntermediateDirectory)/ImageAnalyzer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/ImageAnalyzer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ImageAnalyzer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ImageAnalyzer.cpp$(DependSuffix): ImageAnalyzer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ImageAnalyzer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ImageAnalyzer.cpp$(DependSuffix) -MM "ImageAnalyzer.cpp"

$(IntermediateDirectory)/ImageAnalyzer.cpp$(PreprocessSuffix): ImageAnalyzer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ImageAnalyzer.cpp$(PreprocessSuffix) "ImageAnalyzer.cpp"

$(IntermediateDirectory)/QwopAnalyzer.cpp$(ObjectSuffix): QwopAnalyzer.cpp $(IntermediateDirectory)/QwopAnalyzer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/QwopAnalyzer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/QwopAnalyzer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/QwopAnalyzer.cpp$(DependSuffix): QwopAnalyzer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/QwopAnalyzer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/QwopAnalyzer.cpp$(DependSuffix) -MM "QwopAnalyzer.cpp"

$(IntermediateDirectory)/QwopAnalyzer.cpp$(PreprocessSuffix): QwopAnalyzer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/QwopAnalyzer.cpp$(PreprocessSuffix) "QwopAnalyzer.cpp"

$(IntermediateDirectory)/KeyPresser.cpp$(ObjectSuffix): KeyPresser.cpp $(IntermediateDirectory)/KeyPresser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/KeyPresser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KeyPresser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KeyPresser.cpp$(DependSuffix): KeyPresser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KeyPresser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/KeyPresser.cpp$(DependSuffix) -MM "KeyPresser.cpp"

$(IntermediateDirectory)/KeyPresser.cpp$(PreprocessSuffix): KeyPresser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KeyPresser.cpp$(PreprocessSuffix) "KeyPresser.cpp"

$(IntermediateDirectory)/QwopBot.cpp$(ObjectSuffix): QwopBot.cpp $(IntermediateDirectory)/QwopBot.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/QwopBot.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/QwopBot.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/QwopBot.cpp$(DependSuffix): QwopBot.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/QwopBot.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/QwopBot.cpp$(DependSuffix) -MM "QwopBot.cpp"

$(IntermediateDirectory)/QwopBot.cpp$(PreprocessSuffix): QwopBot.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/QwopBot.cpp$(PreprocessSuffix) "QwopBot.cpp"

$(IntermediateDirectory)/DecisionMaker.cpp$(ObjectSuffix): DecisionMaker.cpp $(IntermediateDirectory)/DecisionMaker.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/matteo/Progetti/QwopBot/DecisionMaker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DecisionMaker.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DecisionMaker.cpp$(DependSuffix): DecisionMaker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DecisionMaker.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DecisionMaker.cpp$(DependSuffix) -MM "DecisionMaker.cpp"

$(IntermediateDirectory)/DecisionMaker.cpp$(PreprocessSuffix): DecisionMaker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DecisionMaker.cpp$(PreprocessSuffix) "DecisionMaker.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Debug/*$(ObjectSuffix)
	$(RM) ./Debug/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/QwopBot"


