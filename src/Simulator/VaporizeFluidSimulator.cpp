
// VaporizeFluidSimulator.cpp

// Implements the cVaporizeFluidSimulator class representing a fluid simulator that replaces all fluid blocks with air

#include "Globals.h"
#include "VaporizeFluidSimulator.h"
#include "../OpaqueWorld.h"
#include "../Chunk.h"
#include "../Blocks/BroadcastInterface.h"





cVaporizeFluidSimulator::cVaporizeFluidSimulator(cWorld & a_World, BLOCKTYPE a_Fluid, BLOCKTYPE a_StationaryFluid) :
	super(a_World, a_Fluid, a_StationaryFluid)
{
}





void cVaporizeFluidSimulator::AddBlock(Vector3i a_Block, cChunk * a_Chunk)
{
	if (a_Chunk == nullptr)
	{
		return;
	}
	int RelX = a_Block.x - a_Chunk->GetPosX() * cChunkDef::Width;
	int RelZ = a_Block.z - a_Chunk->GetPosZ() * cChunkDef::Width;
	BLOCKTYPE BlockType = a_Chunk->GetBlock(RelX, a_Block.y, RelZ);
	if (
		(BlockType == m_FluidBlock) ||
		(BlockType == m_StationaryFluidBlock)
	)
	{
		a_Chunk->SetBlock(RelX, a_Block.y, RelZ, E_BLOCK_AIR, 0);
		World::GetBroadcastInterface(m_World).BroadcastSoundEffect(
			"block.fire.extinguish",
			Vector3d(a_Block),
			1.0f,
			0.6f
		);
	}
}





void cVaporizeFluidSimulator::Simulate(float a_Dt)
{
	// Nothing needed
}




