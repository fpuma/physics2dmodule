#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <precompiledphysics.h>
#include <leo/iphysics.h>
#include <leo/simulation/world/iworld.h>
#include <leo/ids/ids.h>

#include <leo/simulation/frames/frameinfo.h>
#include <leo/simulation/frames/iframe.h>
#include <leo/simulation/frameparts/iframepart.h>

using namespace puma::leo;

TEST( FramePartManagement, AddingRemovingFrameParts )
{
    auto physicsPtr = IPhysics::create();

    WorldID worldId = physicsPtr->addWorld( { 0.0f,0.0f } );
    IWorld* worldPtr = physicsPtr->getWorld( worldId );
    FrameID frameId = worldPtr->addDynamicFrame( {} );
    IFrame* framePtr = physicsPtr->getFrame( frameId );


    //Body
    FramePartID framePartId0 = framePtr->addBody( {} );
    FramePartID framePartId1 = framePtr->addBody( {} );
    FramePartID framePartId2 = framePtr->addBody( {} );
    FramePartID framePartId3 = framePtr->addBody( {} );

    EXPECT_EQ( physicsPtr->getFramePart( framePartId0 )->getID().value(), framePartId0.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId1 )->getID().value(), framePartId1.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId2 )->getID().value(), framePartId2.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId3 )->getID().value(), framePartId3.value() );

    //Trigger
    FramePartID framePartId4 = framePtr->addTrigger( {} );
    FramePartID framePartId5 = framePtr->addTrigger( {} );
    FramePartID framePartId6 = framePtr->addTrigger( {} );
    FramePartID framePartId7 = framePtr->addTrigger( {} );

    EXPECT_EQ( physicsPtr->getFramePart( framePartId4 )->getID().value(), framePartId4.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId5 )->getID().value(), framePartId5.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId6 )->getID().value(), framePartId6.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId7 )->getID().value(), framePartId7.value() );

    //Removing
    framePtr->removeFramePart( framePartId1 );
    framePtr->removeFramePart( framePartId6 );
    
    EXPECT_EQ( physicsPtr->getFramePart( framePartId0 )->getID().value(), framePartId0.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId1 ), nullptr );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId2 )->getID().value(), framePartId2.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId3 )->getID().value(), framePartId3.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId4 )->getID().value(), framePartId4.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId5 )->getID().value(), framePartId5.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId6 ), nullptr );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId7 )->getID().value(), framePartId7.value() );

    //Adding new
    FramePartID framePartId8 = framePtr->addBody( {} );
    FramePartID framePartId9 = framePtr->addTrigger( {} );

    EXPECT_EQ( physicsPtr->getFramePart( framePartId8 )->getID().value(), framePartId8.value() );
    EXPECT_EQ( physicsPtr->getFramePart( framePartId9 )->getID().value(), framePartId9.value() );
}