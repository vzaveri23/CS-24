#include "Person.h"
#include <iostream>

// Person Member Functions

Person::Person(string name, Gender gender, Person *mother, Person *father) {
    this->vname = name;
    this->vgender = gender;
    this->vmother = mother;
    this->vfather = father;
}

const string &Person::name() const {
    return vname;
}

Gender Person::gender() const {
    return vgender;
}

Person* Person::mother() {
    return vmother;
}

Person* Person::father() {
    return vfather;
}

set<Person*> Person::ancestors(PMod pmod) {
    return set<Person*>();
}

set<Person*> Person::aunts(PMod pmod, SMod smod) {
    set<Person*> aunts;
    set<Person*> parents;
    parents = this->parents(pmod);
    for (Person *ptr : parents) {
        aunts.merge(ptr->sisters(PMod::ANY, smod));
    }

    return aunts;
}

set<Person*> Person::brothers(PMod pmod, SMod smod) {
    set<Person*> brothers;
    set<Person*> siblings;

    siblings = this->siblings(pmod, smod);
    for (Person *ptr : siblings) {
        if (ptr->gender() == Gender::MALE) {
            brothers.insert(ptr);
        }
    }

    return brothers;

}

set<Person*> Person::children() {
    return vchildren;
}

set<Person*> Person::cousins(PMod pmod, SMod smod) {
    set<Person*> cousins;
    set<Person*> uncles = this->uncles(pmod, smod);
    set<Person*> aunts = this->aunts(pmod, smod);
    for (Person *ptr : uncles) {
        cousins.merge(ptr->children());
    }

    for (Person* ptr : aunts) {
        cousins.merge(ptr->children());
    }

    return cousins;
}

set<Person*> Person::daughters() {
    set<Person*> daughters;
    for (Person *ptr : vchildren) {
        if (ptr->gender() == Gender::FEMALE) {
            daughters.insert(ptr);
        }
    }

    return daughters;
}

set<Person*> Person::descendants() {
    return set<Person*>();
}

set<Person*> Person::grandchildren() {
    set<Person*> grandchildren;
    grandchildren.merge(granddaughters());
    grandchildren.merge(grandsons());
    return grandchildren;
}

set<Person*> Person::granddaughters() {
    set<Person*> granddaughters;
    for (Person *i : vchildren) {
        for (Person *j : i->children()) {
            if (j->gender() == Gender::FEMALE) {
                granddaughters.insert(j);
            }
        }
    }

    return granddaughters;
}

set<Person*> Person::grandfathers(PMod pmod) {
    set<Person*> grandfathers;
    set<Person*> grandparents;

    grandparents = this->grandparents(pmod);
    for (Person *ptr : grandparents) {
        if (ptr->gender() == Gender::MALE) {
            grandfathers.insert(ptr);
        }
    }

    return grandfathers;
}

set<Person*> Person::grandmothers(PMod pmod) {
    set<Person*> grandmothers;
    set<Person*> grandparents;
    
    grandparents = this->grandparents(pmod);
    for (Person *ptr : grandparents) {
        if (ptr->gender() == Gender::FEMALE) {
            grandmothers.insert(ptr);
        }
    }

    return grandmothers;
}

set<Person*> Person::grandparents(PMod pmod) {
    set<Person*> grandparents;
    set<Person*> parents;
    
    parents = this->parents(pmod);
    for (Person *i : parents) {
        if (i) {
            for (Person *j : i->parents(PMod::ANY)) {
                if (j) {
                    grandparents.insert(j);
                }
            }
        }
    }
    
    return grandparents;
}

set<Person*> Person::grandsons() {
    set<Person*> grandsons;
    for (Person *i : vchildren) {
        for (Person *j : i->children()) {
            if (j->gender() == Gender::MALE) {
                grandsons.insert(j);
            }
        }
    }

    return grandsons;
}

set<Person*> Person::nephews(PMod pmod, SMod smod) {
    set<Person*> nephews;
    set<Person*> siblings;

    siblings = this->siblings(pmod, smod);
    for (Person *i : siblings) {
        nephews.merge(i->sons());
    }

    return nephews;
}

set<Person*> Person::nieces(PMod pmod, SMod smod) {
    set<Person*> nieces;
    set<Person*> siblings;

    siblings = this->siblings(pmod, smod);
    for (Person *i : siblings) {
        nieces.merge(i->daughters());
    }

    return nieces;
}

set<Person*> Person::parents(PMod pmod) {
    set<Person*> parents;
    if (pmod == PMod::MATERNAL) {
        if (mother()) {
            parents.insert(mother());
        }
    } else if (pmod == PMod::PATERNAL) {
        if (father()) {
            parents.insert(father());
        }
    } else {
        if (mother() && father()) {
            parents.insert(mother());
            parents.insert(father());
        }
    }

    return parents;
}

set<Person*> Person::siblings(PMod pmod, SMod smod) {
    set<Person*> siblings;
    set<Person*> parents;
    set<Person*> final;

    parents = this->parents(pmod);
    for (Person *parent : parents) {
        if (parent) {
            siblings.merge(parent->children());
        }
    }

    if (smod == SMod::FULL) {
        for (Person *ptr : siblings) {
            if (father() && ptr->father() == father() && mother() && ptr->mother() == mother()) {
                final.insert(ptr);
            }
        }
    } else if (smod == SMod::HALF) {
        for (Person *ptr : siblings) {
           if ((father() && father() == ptr->father()) != (mother() && mother() == ptr->mother())) {
                final.insert(ptr);
            }
        }
    } else {
        final = siblings;
    }

    final.erase(this);
    return final;
}

set<Person*> Person::sisters(PMod pmod, SMod smod) {
    set<Person*> sisters;
    set<Person*> siblings;

    siblings = this->siblings(pmod, smod);
    for (Person *ptr : siblings) {
        if (ptr->gender() == Gender::FEMALE) {
            sisters.insert(ptr);
        }
    }

    return sisters;
}

set<Person*> Person::sons() {
    set<Person*> sons;
    for (Person *ptr : vchildren) {
        if (ptr->gender() == Gender::MALE) {
            sons.insert(ptr);
        }
    }

    return sons;
}

set<Person*> Person::uncles(PMod pmod, SMod smod) {
    set<Person*> uncles;
    set<Person*> parents;
    parents = this->parents(pmod);
    for (Person *ptr : parents) {
        uncles.merge(ptr->brothers(PMod::ANY, smod));
    }

   return uncles;
    
}

void Person::addChild(Person *ptr) {
    vchildren.insert(ptr);
}




