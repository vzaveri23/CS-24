#include "Person.h"

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

   if (pmod == PMod::MATERNAL) {
    aunts = mother()->sisters(pmod, smod);
   } else if (pmod == PMod::PATERNAL) {
    aunts = father()->sisters(pmod, smod);
   } else {
    aunts.merge(mother()->sisters(pmod, smod));
    aunts.merge(father()->sisters(pmod, smod));
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
    set<Person*> siblings;
    if (pmod == PMod::MATERNAL) {
        siblings = mother()->siblings(pmod, smod);
        for (Person *i : siblings) {
            for (Person *j : i->children()) {
                cousins.insert(j);
            }
        }
    } else if (pmod == PMod::PATERNAL) {
        siblings = father()->siblings(pmod, smod);
        for (Person *i : siblings) {
            for (Person *j : i->children()) {
                cousins.insert(j);
            }
        }
    } else {

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
    if (pmod == PMod::MATERNAL) {
        grandfathers.insert(mother()->father());
    } else if (pmod == PMod::PATERNAL) {
        grandfathers.insert(father()->father());
    } else {
        grandfathers.insert(mother()->father());
        grandfathers.insert(father()->father());
    }

    return grandfathers;
}

set<Person*> Person::grandmothers(PMod pmod) {
    set<Person*> grandmothers;
    if (pmod == PMod::MATERNAL) {
        grandmothers.insert(mother()->mother());
    } else if (pmod == PMod::PATERNAL) {
        grandmothers.insert(father()->mother());
    } else {
        grandmothers.insert(mother()->mother());
        grandmothers.insert(father()->mother());
    }

    return grandmothers;
}

set<Person*> Person::grandparents(PMod pmod) {
    set<Person*> grandparents;
    grandparents.merge(grandfathers(pmod));
    grandparents.merge(grandmothers(pmod));
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
        // for (Person *j : i->sons()) {
        //     nephews.insert(j);
        // }
        nephews.merge(i->sons());
    }

    return nephews;
}

set<Person*> Person::nieces(PMod pmod, SMod smod) {
    set<Person*> nieces;
    set<Person*> siblings;

    siblings = this->siblings(pmod, smod);
    for (Person *i : siblings) {
        // for (Person *j : i->daughters()) {
        //     nieces.insert(j);
        // }
        nieces.merge(i->daughters());
    }

    return nieces;
}

set<Person*> Person::parents(PMod pmod) {
    set<Person*> parents;
    if (pmod == PMod::MATERNAL) {
        parents.insert(mother());
    } else if (pmod == PMod::PATERNAL) {
        parents.insert(father());
    } else {
        parents.insert(mother());
        parents.insert(father());
    }

    return parents;
}

set<Person*> Person::siblings(PMod pmod, SMod smod) {
    set<Person*> siblings;
    set<Person*> parents;
    // if (pmod == PMod::PATERNAL) {
    //     for (Person *ptr : vfather->children()) {
    //         siblings.insert(ptr);
    //     }
    // } else if (pmod == PMod::MATERNAL) {
    //     for (Person *ptr : vmother->children()) {
    //         siblings.insert(ptr);
    //     }
    // } else {
    //    for (Person *ptr : vfather->children()) {
    //         siblings.insert(ptr);
    //     }

    //      for (Person *ptr : vmother->children()) {
    //         siblings.insert(ptr);
    //     }
    // }

    parents = this->parents(pmod);
    for (Person *parent : parents) {
        siblings.merge(parent->children());
    }

    if (smod == SMod::FULL) {
        for (Person *ptr : siblings) {
            if (!ptr->father() || ptr->father() != father() || !ptr->mother() || ptr->mother() != mother()) {
                siblings.erase(ptr);
            }
        }
    } else if (smod == SMod::HALF) {
        for (Person *ptr : siblings) {
           if ((father() && father() == ptr->father()) != (mother() && mother() == ptr->mother()))
                siblings.erase(ptr);
            }
    }

    siblings.erase(this);
    return siblings;
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

   if (pmod == PMod::MATERNAL) {
    uncles = mother()->brothers(pmod, smod);
   } else if (pmod == PMod::PATERNAL) {
    uncles = father()->brothers(pmod, smod);
   } else {
    uncles.merge(mother()->brothers(pmod, smod));
    uncles.merge(father()->brothers(pmod, smod));
   }

   return uncles;
    
}

void Person::addChild(Person *ptr) {
    vchildren.insert(ptr);
}




