#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <precompiledphysics.h>
#include <leo/iphysics.h>
#include <leo/simulation/world/iworld.h>
#include <leo/ids/ids.h>

using namespace puma::leo;

TEST( WorldManagement, WorldCountCap )
{
    auto physicsPtr = IPhysics::create();

    WorldID worldId0 = physicsPtr->addWorld( { 0.0f,0.0f } );
    WorldID worldId1 = physicsPtr->addWorld( { 0.0f,0.0f } );
    WorldID worldId2 = physicsPtr->addWorld( { 0.0f,0.0f } );
    WorldID worldId3 = physicsPtr->addWorld( { 0.0f,0.0f } );

    EXPECT_DEATH( physicsPtr->addWorld( { 0.0f,0.0f } ), "m_worldCount < kMaxWorldCount" );
}

TEST( WorldManagement, AddingRemovingWorlds )
{
    auto physicsPtr = IPhysics::create();

    WorldID worldId0 = physicsPtr->addWorld( { 0.0f,0.0f } );
    WorldID worldId1 = physicsPtr->addWorld( { 0.0f,0.0f } );
    WorldID worldId2 = physicsPtr->addWorld( { 0.0f,0.0f } );
    WorldID worldId3 = physicsPtr->addWorld( { 0.0f,0.0f } );

    EXPECT_EQ( physicsPtr->getWorld( worldId0 )->getWorldID().value(), worldId0.value() );
    EXPECT_EQ( physicsPtr->getWorld( worldId1 )->getWorldID().value(), worldId1.value() );
    EXPECT_EQ( physicsPtr->getWorld( worldId2 )->getWorldID().value(), worldId2.value() );
    EXPECT_EQ( physicsPtr->getWorld( worldId3 )->getWorldID().value(), worldId3.value() );

    physicsPtr->removeWorld( worldId1 );

    EXPECT_EQ( physicsPtr->getWorld( worldId0 )->getWorldID().value(), worldId0.value() );
    EXPECT_EQ( physicsPtr->getWorld( worldId1 ), nullptr );
    EXPECT_EQ( physicsPtr->getWorld( worldId2 )->getWorldID().value(), worldId2.value() );
    EXPECT_EQ( physicsPtr->getWorld( worldId3 )->getWorldID().value(), worldId3.value() );

    WorldID worldId4 = physicsPtr->addWorld( { 0.0f,0.0f } );
    EXPECT_EQ( physicsPtr->getWorld( worldId4 )->getWorldID().value(), worldId4.value() );
}