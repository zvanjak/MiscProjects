// CodeAnalyzer_ConsoleRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <list>

#include "..\CodeAnalyzerLib\CodeModel.h"
#include "..\CodeAnalyzerLib\CodeModelCreator.h"
#include "..\CodeAnalyzerLib\AnalysisInput.h"
#include "..\CodeAnalyzerLib\AnalysisPerformers.h"

using namespace std;

using namespace CodeAnalyzer;

int _tmain(int argc, _TCHAR* argv[])
{
	AnalysisInput			inputCrit;
	CodeModelCreator	modelCreator;
	CodeModel::PhysicalCodeModel	analysisInput;

	// definiramo što æemo analizirati
//	inputCrit.AddProject("ESOPCppLib", "D:\\CRS\\Crest\\CrestGASolver\\ESOPCppLib", true, CodeModel::ProjectTypes::CPP);
//	inputCrit.AddProject("CrestGASolverLib", "D:\\CRS\\Crest\\CrestGASolver\\CrestGASolverLib", false, CodeModel::ProjectTypes::CPP);
//	inputCrit.AddProject("DeMakVisualizer", "D:\\CRS\\Crest\\CrestGASolver\\DeMakVisualizer", false, CodeModel::ProjectTypes::CPP);
//	inputCrit.AddProject("Nevron3DParetoSetVisualizier", "D:\\CRS\\Crest\\CrestGASolver\\Nevron3DParetoSetVisualizier", false, CodeModel::ProjectTypes::CSharp);
//	inputCrit.AddProject("CodeAnalyzerLib", "D:\\Users\\Zvone\\Projects\\CodeAnalyzer\\Iteracija 1\\C++\\CodeAnalyzerLib", false, CodeModel::ProjectTypes::CPP);
//	inputCrit.AddProject("ESOP", "D:\\ESOP\\Code", true, CodeModel::ProjectTypes::CPP);
//	inputCrit.AddProject("ESOP", "D:\\ESOP\\Code", true, CodeModel::ProjectTypes::CSharp);
	
	inputCrit.AddProject("topXview GUI project", "D:\\Source\\SOURCE\\PROGS\\TXV_GUI\\branches\\1.75", true, CodeModel::ProjectTypes::CPP);
//	inputCrit.AddProject("EddyOneAcquisition external lib", "E:\\Development\\EddyOneAquisition\\Lib", true, CodeModel::ProjectTypes::CPP);
/*
	inputCrit.AddProject("EddyOneAnalysis", "E:\\Development\\EddyOneAnalysis", true, CodeModel::ProjectTypes::CPP);
	inputCrit.AddProject("EddyOneAcquisition", "E:\\Development\\EddyOneAquisition", true, CodeModel::ProjectTypes::CPP);
	inputCrit.AddProject("Elvis", "E:\\Development\\ElvisRoot", true, CodeModel::ProjectTypes::CSharp);
	inputCrit.AddProject("GraphControl", "E:\\Development\\GraphControl", true, CodeModel::ProjectTypes::CSharp);
	inputCrit.AddProject("InspectionManagement", "E:\\Development\\InspectionManagement", true, CodeModel::ProjectTypes::CSharp);
	inputCrit.AddProject("Manipulator control", "E:\\Development\\ManipulatorControl", true, CodeModel::ProjectTypes::CSharp);
	inputCrit.AddProject("Plugging control", "E:\\Development\\Plugging Control", true, CodeModel::ProjectTypes::CSharp);
	inputCrit.AddProject("SM Manipulator", "E:\\Development\\SMManipulator", true, CodeModel::ProjectTypes::CSharp);
*/	
	// na osnovu definiranih input-a se kreira code model koji æe se analizirati
	modelCreator.CreatePhysicalCodeModel(inputCrit, analysisInput);

	// kreiramo "analizator" (za analizu fizièkih karakteristika koda)
	Analyzers::ModelPhysicalLayoutAnalyzer		analysisPerformer;

	cout << "START" << endl;

	analysisPerformer.Analyze(analysisInput);

	return 0;
}

