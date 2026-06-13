#pragma once
#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>

class Activity { //// Parent class
private:
    std::string idActivity;
    std::string name;
    std::string description;
    std::string schedule;
public:
   // Activity(const std::string& id, const std::string& nm, const std::string& desc, const std::string& sched)
    //    : idActivity(id), name(nm), description(desc), schedule(sched) {
    
    //function that teaches cout how to print a complete Activity object
    friend std::ostream& operator<<(std::ostream& os, const Activity& act) {
        os << act.getName() << " | Schedule: " << act.getSchedule();
        return os;
    }

    virtual ~Activity() {}
    //// THE GETTERS
    std::string getId() const { return idActivity; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    std::string getSchedule() const { return schedule; }
};
// Child class
class GentleExercise : public Activity { 
public:
    GentleExercise() : Activity("01", "Gentle Exercise / Mobility Exercises", "Light movements to improve circulation, flexibility, and balance.", "Mon & Wed - 09:00 AM to 10:30 AM (Matutino)") {}
};
class ArtsAndCrafts : public Activity {
public:
    ArtsAndCrafts() : Activity("02", "Arts and Crafts", "Painting, knitting, drawing, or paper crafts to stimulate creativity.", "Tue & Thu - 04:00 PM to 06:00 PM (Vespertino)") {}
};
class MusicAndSinging : public Activity {
public:
    MusicAndSinging() : Activity("03", "Music and Singing", "Listening to music from their era, group singing, simple instruments.", "Fridays - 10:00 AM to 12:00 PM (Matutino)") {}
};
class CognitiveStimulation : public Activity {
public:
    CognitiveStimulation() : Activity("04", "Cognitive Stimulation", "Memory games, puzzles, word searches, and mental exercises.", "Mon & Wed - 05:00 PM to 07:00 PM (Vespertino)") {}
};
class ReadingAndWriting : public Activity {
public:
    ReadingAndWriting() : Activity("05", "Reading and Writing", "Reading aloud, book clubs, or writing personal stories and memories.", "Tue & Thu - 09:00 AM to 11:00 AM (Matutino)") {}
};
class TherapeuticDance : public Activity {
public:
    TherapeuticDance() : Activity("06", "Therapeutic Dance", "Slow, adapted dancing to improve coordination and mood.", "Fridays - 04:00 PM to 06:00 PM (Vespertino)") {}
};
class BoardGames : public Activity {
public:
    BoardGames() : Activity("07", "Board Games", "Dominoes, cards, bingo, or chess to encourage social interaction.", "Saturdays - 10:00 AM to 12:00 PM (Matutino)") {}
};
class SocialInteraction : public Activity {
public:
    SocialInteraction() : Activity("08", "Social Interaction / Group Talks", "Guided conversations, birthday celebrations, group activities.", "Saturdays - 04:00 PM to 06:00 PM (Vespertino)") {}
};

#endif