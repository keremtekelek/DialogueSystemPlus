#include "FunctionLibraries/FunctionLibrary_DialogueScanner.h"
#include "DialogueWriter/DialogueWriter.h"






void UFunctionLibrary_DialogueScanner::ScanAndExport(UDialogueWriter* DialogueWriterCPP)
{
    if (!(IsValid(DialogueWriterCPP)))
    {
        UE_LOG(LogTemp, Warning, TEXT("DialogueWriter sinifi valid degil!"))
        return;
    }

    UClass* DialogueWriterClass = DialogueWriterCPP->GetClass();
    UBlueprint* BP_DialogueWriter = Cast<UBlueprint>(DialogueWriterClass->ClassGeneratedBy);

    if (!(IsValid(BP_DialogueWriter)))
    {
        UE_LOG(LogTemp, Warning, TEXT("BP_DialogueWriter valid degil!"))
        return;
    }

    for (UEdGraph* Graph : BP_DialogueWriter->UbergraphPages)
    {
        for (UEdGraphNode* Node : Graph->Nodes)
        {
            UK2Node_CallFunction* CallFuncNode = Cast<UK2Node_CallFunction>(Node);
            if (!CallFuncNode) continue;

            FName FunctionName = CallFuncNode->GetFunctionName();

            if (FunctionName == FName("NPC_Dialogue_Node"))
            {
                FGuid NodeID = Node->NodeGuid;
                FString NodeID_string = NodeID.ToString();
                FName NodeID_name(*NodeID_string);
                
                FNPC_Dialogues NewNPC;
                
                NewNPC.DialogueID = NodeID_name;
            }
        }
    }
    
        
}