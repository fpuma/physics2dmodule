#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <precompiledphysics.h>
#include <leo/iphysics.h>
#include <leo/simulation/world/iworld.h>
#include <leo/ids/ids.h>

#include <leo/simulation/frames/frameinfo.h>
#include <leo/simulation/frames/iframe.h>

using namespace puma::leo;

TEST( FrameManagement, AddingRemovingFrames )
{
    auto physicsPtr = IPhysics::create();

    WorldID worldId = physicsPtr->addWorld( { 0.0f,0.0f } );
    IWorld* worldPtr = physicsPtr->getWorld( worldId );

    worldPtr->setReuseRemovedIds(false);

    //Dynamic
    FrameID frameId0 = worldPtr->addDynamicFrame( {} );
    FrameID frameId1 = worldPtr->addDynamicFrame( {} );
    FrameID frameId2 = worldPtr->addDynamicFrame( {} );
    FrameID frameId3 = worldPtr->addDynamicFrame( {} );

    EXPECT_EQ( physicsPtr->getFrame( frameId0 )->getID().value(), frameId0.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId1 )->getID().value(), frameId1.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId2 )->getID().value(), frameId2.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId3 )->getID().value(), frameId3.value() );

    //Static
    FrameID frameId4 = worldPtr->addStaticFrame( {} );
    FrameID frameId5 = worldPtr->addStaticFrame( {} );
    FrameID frameId6 = worldPtr->addStaticFrame( {} );
    FrameID frameId7 = worldPtr->addStaticFrame( {} );

    EXPECT_EQ( physicsPtr->getFrame( frameId4 )->getID().value(), frameId4.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId5 )->getID().value(), frameId5.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId6 )->getID().value(), frameId6.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId7 )->getID().value(), frameId7.value() );

    //Kinematic
    FrameID frameId8 = worldPtr->addKinematicFrame( {} );
    FrameID frameId9 = worldPtr->addKinematicFrame( {} );
    FrameID frameId10 = worldPtr->addKinematicFrame( {} );
    FrameID frameId11 = worldPtr->addKinematicFrame( {} );

    EXPECT_EQ( physicsPtr->getFrame( frameId8 )->getID().value(), frameId8.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId9 )->getID().value(), frameId9.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId10 )->getID().value(), frameId10.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId11 )->getID().value(), frameId11.value() );

    //Removing
    worldPtr->removeFrame( frameId1 );
    worldPtr->removeFrame( frameId6 );
    worldPtr->removeFrame( frameId9 );

    EXPECT_EQ( physicsPtr->getFrame( frameId0 )->getID().value(), frameId0.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId1 ), nullptr );
    EXPECT_EQ( physicsPtr->getFrame( frameId2 )->getID().value(), frameId2.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId3 )->getID().value(), frameId3.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId4 )->getID().value(), frameId4.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId5 )->getID().value(), frameId5.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId6 ), nullptr );
    EXPECT_EQ( physicsPtr->getFrame( frameId7 )->getID().value(), frameId7.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId8 )->getID().value(), frameId8.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId9 ), nullptr );
    EXPECT_EQ( physicsPtr->getFrame( frameId10 )->getID().value(), frameId10.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId11 )->getID().value(), frameId11.value() );

    //Adding new
    FrameID frameId12 = worldPtr->addDynamicFrame( {} );
    FrameID frameId13 = worldPtr->addStaticFrame( {} );
    FrameID frameId14 = worldPtr->addKinematicFrame( {} );

    EXPECT_EQ(physicsPtr->getFrame(frameId1), nullptr);
    EXPECT_EQ(physicsPtr->getFrame(frameId6), nullptr);
    EXPECT_EQ(physicsPtr->getFrame(frameId9), nullptr);

    EXPECT_EQ( physicsPtr->getFrame( frameId12 )->getID().value(), frameId12.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId13 )->getID().value(), frameId13.value() );
    EXPECT_EQ( physicsPtr->getFrame( frameId14 )->getID().value(), frameId14.value() );
}