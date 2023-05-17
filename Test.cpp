#include "doctest.h"
#include "sources/Point.hpp"
#include "sources/Character.hpp"
#include "sources/Team.hpp"

TEST_CASE("Two points distance calculation"){
    ariel::Point p1(0,0);
    ariel::Point p2(3,4);
    CHECK(p1.distance(p2) == 5);
    CHECK(p2.distance(p1) == 5);
    CHECK(p1.distance(p1) == 0);
    CHECK(p2.distance(p2) == 0);
}
TEST_CASE("Moving a point toward test"){
    ariel::Point p1(0,0);
    ariel::Point p2(-3,6);
    ariel::Point p3(1,-3);
    SUBCASE("Moving a point toward with a positive distance"){
        CHECK(moveTowards(p1,p2,2).distance(p1) == 2);
        CHECK(moveTowards(p1,p2,2).distance(p2) == (p1.distance(p2)) - 2);
        CHECK(moveTowards(p1,p2,0).getX() == p1.getX());
        CHECK(moveTowards(p1,p2,0).getY() == p1.getY());
    }
    SUBCASE("Moving a point toward with a negative distance"){
        CHECK_THROWS(moveTowards(p1,p2,-0.3));
    }
}
TEST_CASE("Not throwing exception point print"){
    ariel::Point p1(0,0);
    CHECK_NOTHROW(p1.print());
}
TEST_SUITE("Characters initialization"){
    TEST_CASE("Young Ninja initialization"){
        ariel::YoungNinja young_ninja1("Young Ninja", ariel::Point(5.6,-1.3));
        CHECK(young_ninja1.getName() == "Young Ninja");
        CHECK(young_ninja1.getLocation().getX() == -1.3);
        CHECK(young_ninja1.getLocation().getY() == 5.6);
        CHECK(young_ninja1.isAlive() == true);
        CHECK(young_ninja1.getHealthPoints() == 100);
    }
    TEST_CASE("Trained Ninja initialization"){
        ariel::TrainedNinja trained_ninja1("Trained Ninja", ariel::Point(5.6,-1.3));
        CHECK(trained_ninja1.getName() == "Trained Ninja");
        CHECK(trained_ninja1.getLocation().getX() == -1.3);
        CHECK(trained_ninja1.getLocation().getY() == 5.6);
        CHECK(trained_ninja1.isAlive() == true);
        CHECK(trained_ninja1.getHealthPoints() == 120);
    }

    TEST_CASE("Old Ninja initialization"){
        ariel::OldNinja old_ninja1("Old Ninja", ariel::Point(5.6,-1.3));
        CHECK(old_ninja1.getName() == "Old Ninja");
        CHECK(old_ninja1.getLocation().getX() == -1.3);
        CHECK(old_ninja1.getLocation().getY() == 5.6);
        CHECK(old_ninja1.isAlive() == true);
        CHECK(old_ninja1.getHealthPoints() == 150);
    }

    TEST_CASE("Cowboy initialization"){
        ariel::Cowboy cowboy1("Cowboy", ariel::Point(5.6,-1.3));
        CHECK(cowboy1.getName() == "Cowboy");
        CHECK(cowboy1.getLocation().getX() == -1.3);
        CHECK(cowboy1.getLocation().getY() == 5.6);
        CHECK(cowboy1.isAlive() == true);
        CHECK(cowboy1.getHealthPoints() == 110);
        CHECK(cowboy1.hasboolets() == true);
    }   
}
TEST_SUITE("Characters attack"){
    TEST_CASE("Cowboy attack-Ninja hit"){
        SUBCASE("Cowboy attack-Young Ninja hit"){
            ariel::Cowboy cowboy("Cowboy", ariel::Point(5.6,-1.3));
            ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
            ariel::TrainedNinja trained_ninja("Trained Ninja", ariel::Point(5.6,-1.3));
            ariel::OldNinja old_ninja("Old Ninja", ariel::Point(5.6,-1.3));
            int bullets_count = 0;
            while (cowboy.hasboolets())
            {
                cowboy.shoot(&young_ninja);
                bullets_count++;
                CHECK(young_ninja.getHealthPoints() == (100 - bullets_count * 10));
                if (bullets_count > 6)
                {
                    // The cowboy has 6 bullets, so after 6 shots he should not have any bullets left
                    CHECK(false);
                    break;
                }
            }
        }
        SUBCASE("Cowboy kill-Trained Ninja"){
            ariel::Cowboy cowboy("Cowboy", ariel::Point(5.6,-1.3));
            ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
            ariel::TrainedNinja trained_ninja("Trained Ninja", ariel::Point(5.6,-1.3));
            ariel::OldNinja old_ninja("Old Ninja", ariel::Point(5.6,-1.3));
            int bullets_count = 0;
            cowboy.reload();
            while (cowboy.hasboolets())
            {
                cowboy.shoot(&trained_ninja);
                bullets_count++;
                CHECK(trained_ninja.getHealthPoints() == (120 - bullets_count * 10));
                if (bullets_count % 6 == 0){
                    cowboy.reload();
                }
                if (bullets_count > 12){
                    // The cowboy has 12 bullets, so after 12 shots he should not have any bullets left
                    CHECK(false);
                    break;
                }
                CHECK_FALSE(trained_ninja.isAlive());
            }
        }
        SUBCASE("Cowboy kill-Old Ninja"){
            ariel::Cowboy cowboy("Cowboy", ariel::Point(5.6,-1.3));
            ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
            ariel::TrainedNinja trained_ninja("Trained Ninja", ariel::Point(5.6,-1.3));
            ariel::OldNinja old_ninja("Old Ninja", ariel::Point(5.6,-1.3));
            int bullets_count = 0;
            cowboy.reload();
            while (cowboy.hasboolets())
            {
                cowboy.shoot(&old_ninja);
                bullets_count++;
                CHECK(old_ninja.getHealthPoints() == (150 - bullets_count * 10));
                if (bullets_count % 6 == 0){
                    cowboy.reload();
                }
                if (bullets_count > 15){
                    // The cowboy has 15 bullets, so after 15 shots he should not have any bullets left
                    CHECK(false);
                    break;
                }
                CHECK_FALSE(old_ninja.isAlive());
            }
        }
    }
    TEST_CASE("Ninja attack - Cowboy hit"){
        ariel::Cowboy cowboy("Cowboy", ariel::Point(5.6,-1.3));
        ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
        ariel::TrainedNinja trained_ninja("Trained Ninja", ariel::Point(5.6,-1.3));
        ariel::OldNinja old_ninja("Old Ninja", ariel::Point(5.6,-1.3));
        young_ninja.slash(&cowboy);
        CHECK(cowboy.getHealthPoints() == 70);
        young_ninja.slash(&cowboy);
        CHECK(cowboy.getHealthPoints() == 30);
        CHECK_NOTHROW(young_ninja.slash(&cowboy));
        CHECK(cowboy.getHealthPoints() == 0);
        CHECK_FALSE(cowboy.isAlive());
    }
    TEST_CASE("Cowboy shooting without bullets"){
        ariel::Cowboy cowboy("Cowboy", ariel::Point(5.6,-1.3));
        ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
        while (cowboy.hasboolets())
        {
            cowboy.shoot(&young_ninja);
        }
        CHECK_FALSE(cowboy.hasboolets());
        CHECK_THROWS(cowboy.shoot(&young_ninja));
    }
    TEST_CASE("Attack not alive character")
    {
        ariel::Cowboy cowboy("Cowboy", ariel::Point(5.6,-1.3));
        ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
        while (young_ninja.isAlive())
        {
            cowboy.shoot(&young_ninja);
            if (!cowboy.hasboolets())
            {
                cowboy.reload();
            }
        }
        cowboy.shoot(&young_ninja);
        CHECK_FALSE(young_ninja.isAlive());
        CHECK(young_ninja.getHealthPoints() == 0);
    }
}
TEST_SUITE("Characters moving toward test"){
    TEST_CASE("Young Ninja moving"){
        SUBCASE("Young Ninja moving toward cowboy"){
            ariel::Cowboy cowboy("Cowboy", ariel::Point(20,-30));
            ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
            ariel::Point prev_location = young_ninja.getLocation();
            young_ninja.move(&cowboy);
            CHECK(young_ninja.getLocation().distance(prev_location) == 14);
            CHECK_EQ(prev_location.distance(cowboy.getLocation()), young_ninja.getLocation().distance(cowboy.getLocation()) + 14);
        }
        SUBCASE("Young Ninja moving toward other Ninja"){
            ariel::Cowboy old_ninja("Old Ninja", ariel::Point(20,-30));
            ariel::YoungNinja young_ninja("Young Ninja", ariel::Point(5.6,-1.3));
            ariel::Point prev_location = young_ninja.getLocation();
            young_ninja.move(&old_ninja);
            CHECK(young_ninja.getLocation().distance(prev_location) == 14);
            CHECK_EQ(prev_location.distance(old_ninja.getLocation()), young_ninja.getLocation().distance(old_ninja.getLocation()) + 14);
        }
    }
    TEST_CASE("Trained Ninja moving"){
        ariel::Cowboy cowboy("Cowboy", ariel::Point(20,-30));
        ariel::TrainedNinja trained_ninja("Trained Ninja", ariel::Point(5.6,-1.3));
        ariel::Point prev_location = trained_ninja.getLocation();
        trained_ninja.move(&cowboy);
        CHECK(trained_ninja.getLocation().distance(prev_location) == 12);
        CHECK_EQ(prev_location.distance(cowboy.getLocation()), trained_ninja.getLocation().distance(cowboy.getLocation()) + 12);
    }
    TEST_CASE("Old Ninja moving"){
        ariel::Cowboy cowboy("Cowboy", ariel::Point(20,-30));
        ariel::OldNinja old_ninja("Old Ninja", ariel::Point(5.6,-1.3));
        ariel::Point prev_location = old_ninja.getLocation();
        old_ninja.move(&cowboy);
        CHECK(old_ninja.getLocation().distance(prev_location) == 8);
        CHECK_EQ(prev_location.distance(cowboy.getLocation()), old_ninja.getLocation().distance(cowboy.getLocation()) + 8);
    }
}
TEST_CASE("Not throwing exception character print"){
    ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
    ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
    ariel::Character* c3 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(5.6,-1.3));
    ariel::Character* c4 = new ariel::OldNinja("Old Ninja", ariel::Point(5.6,-1.3));
    CHECK_NOTHROW({
        c1->print();
        c2->print();
        c3->print();
        c4->print();
    });
    delete c1;
    delete c2;
    delete c3;
    delete c4;
}

TEST_SUITE("Team initialization test"){
    TEST_CASE("Team initialization"){
        ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
        ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
        ariel::Character* c3 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(5.6,-1.3));
        ariel::Character* c4 = new ariel::OldNinja("Old Ninja", ariel::Point(5.6,-1.3));
        ariel::Team team(c1);
        CHECK_NOTHROW(team.add(c2));
        CHECK_NOTHROW(team.add(c3));
        CHECK_NOTHROW(team.add(c4));
        CHECK_NOTHROW(team.print());
        CHECK_EQ(team.stillAlive(), 4);
    }
    TEST_CASE("Team2 initialization"){
        ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
        ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
        ariel::Character* c3 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(5.6,-1.3));
        ariel::Character* c4 = new ariel::OldNinja("Old Ninja", ariel::Point(5.6,-1.3));
        ariel::Team2 team2(c4);
        CHECK_NOTHROW(team2.add(c1));
        CHECK_NOTHROW(team2.add(c2));
        CHECK_NOTHROW(team2.add(c3));
        CHECK_NOTHROW(team2.print());
        CHECK_EQ(team2.stillAlive(), 4);
    }
    TEST_CASE("SmartTeam initialization"){
        ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
        ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
        ariel::Character* c3 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(5.6,-1.3));
        ariel::Character* c4 = new ariel::OldNinja("Old Ninja", ariel::Point(5.6,-1.3));
        ariel::SmartTeam smart_team(c4);
        CHECK_NOTHROW(smart_team.add(c1));
        CHECK_NOTHROW(smart_team.add(c2));
        CHECK_NOTHROW(smart_team.add(c3));
        CHECK_NOTHROW(smart_team.print());
        CHECK_EQ(smart_team.stillAlive(), 4);
    }
}
TEST_CASE("Adding leader as a member of the team throws exception"){
    ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
    ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
    ariel::Team team(c1);
    CHECK_NOTHROW(team.add(c2));
    CHECK_THROWS(team.add(c1));
}
TEST_CASE("Adding same character twice throws exception"){
    ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
    ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
    ariel::Team team(c1);
    CHECK_NOTHROW(team.add(c2));
    CHECK_THROWS(team.add(c2));
}
TEST_CASE("No same member in different teams"){
    ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
    ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(5.6,-1.3));
    ariel::Character* c3 = new ariel::OldNinja("Old Ninja", ariel::Point(5.6,-1.3));
    ariel::Team team(c1);
    ariel::Team team2(c2);
    CHECK_NOTHROW(team.add(c3));
    //CHECK_THROWS(team2.add(c3));
}
TEST_CASE("No same leader in different teams"){
    ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(5.6,-1.3));
    CHECK_NOTHROW(ariel::Team team(c1));
    //CHECK_THROWS((ariel::SmartTeam(c1)));
}
TEST_SUITE("Teams attack tests"){
    TEST_CASE("Team vs Team2 attack"){
        ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(1, 0));
        ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(-2.1, -1.0));
        ariel::Character* c3 = new ariel::OldNinja("Old Ninja", ariel::Point(3, 5.2));
        ariel::Character* ca1 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(10,-2));
        ariel::Character* ca2 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(5,-3.5));
        ariel::Team team(c1);
        team.add(c2);
        team.add(c3);
        ariel::Team2 team2(ca1);
        team2.add(ca2);
        CHECK_NOTHROW(team.attack(&team2));
        CHECK_GE(team2.stillAlive(), 1);
        CHECK_NOTHROW(team2.attack(&team));
        CHECK_GE(team.stillAlive(), 2);
        // in high probability the team2 will be defeated
        for (size_t i = 0; i < 10; i++){
            try{
                team.attack(&team2);
            }
            catch(const std::exception& e){
                continue;
            }
            
        }
        CHECK_EQ(team2.stillAlive(), 0);
        // The team is dead, so it can't be under attack
        CHECK_THROWS(team.attack(&team2));
    }
    TEST_CASE("Team vs SmartTeam attack"){
        ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(1, 0));
        ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(-2.1, -1.0));
        ariel::Character* c3 = new ariel::OldNinja("Old Ninja", ariel::Point(3, 5.2));
        ariel::Character* ca1 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(10,-2));
        ariel::Character* ca2 = new ariel::TrainedNinja("Trained Ninja", ariel::Point(5,-3.5));
        ariel::Team team(c1);
        team.add(c2);
        team.add(c3);
        ariel::SmartTeam smart_team(ca1);
        smart_team.add(ca2);
        CHECK_NOTHROW(team.attack(&smart_team));
        CHECK_GE(smart_team.stillAlive(), 1);
        CHECK_NOTHROW(smart_team.attack(&team));
        CHECK_GE(team.stillAlive(), 2);
        // in high probability the smart team will be defeated
        for (size_t i = 0; i < 10; i++){
            try{
                team.attack(&smart_team);
            }
            catch(const std::exception& e){
                continue;
            }
            
        }
        CHECK_EQ(smart_team.stillAlive(), 0);
        // The team is dead, so it can't be under attack
        CHECK_THROWS(team.attack(&smart_team));
    }
    TEST_CASE("Self attack is invalid"){
        ariel::Character* c1 = new ariel::Cowboy("Cowboy", ariel::Point(1, 0));
        ariel::Character* c2 = new ariel::YoungNinja("Young Ninja", ariel::Point(-2.1, -1.0));
        ariel::Character* c3 = new ariel::OldNinja("Old Ninja", ariel::Point(3, 5.2));
        ariel::Team team(c1);
        team.add(c2);
        team.add(c3);
        CHECK_THROWS(team.attack(&team));
    }   
}