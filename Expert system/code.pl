guess:- animal_is(Animal),
        write('I guess that the animal is: '),
        write(Animal),
        nl,
        undo.
 
/* 7 animals in database to verify */
animal_is(cheetah)   :- cheetah, !.
animal_is(tiger)     :- tiger, !.
animal_is(giraffe)   :- giraffe, !.
animal_is(zebra)     :- zebra, !.
animal_is(ostrich)   :- ostrich, !.
animal_is(penguin)   :- penguin, !.
animal_is(albatross) :- albatross, !.
animal_is(unknown).             /* no diagnosis */
 
/* knowledge base 15 rules */
it_is(mammal) :- verify(has_hair), !.

it_is(mammal) :- verify(gives_milk).

it_is(bird)   :- verify(has_feathers), !.

it_is(bird)   :- verify(flys), 
                 verify(lays_eggs).

it_is(carnivore) :- verify(eats_meat), !.

it_is(carnivore) :- verify(has_canine_teeth), 
                    verify(has_claws),
                    verify(has_forward_eyes).

it_is(ungulate) :- it_is(mammal), 
                   verify(has_hooves), !.

it_is(ungulate) :- it_is(mammal), 
                   verify(chews_cud).

cheetah :- it_is(mammal), 
           it_is(carnivore), 
           verify(has_tawny_color),
           verify(has_dark_spots).

tiger :- it_is(mammal),  
         it_is(carnivore),
         verify(has_tawny_color), 
         verify(has_black_stripes).

giraffe :- it_is(ungulate), 
           verify(has_long_neck), 
           verify(has_long_legs),
           verify(has_dark_spots).

zebra :- it_is(ungulate),  
         verify(has_black_stripes).
 
ostrich :- it_is(bird),  
           verify(not_fly), 
           verify(has_long_neck),
           verify(has_long_legs),
           verify(has_black_white_color).

penguin :- it_is(bird), 
           verify(not_fly), 
           verify(swims),
           verify(has_black_white_color).

albatross :- it_is(bird),
             verify(flys_well).
 
 
/* ask questions to get clues */
ask(Question) :-
    write('Does the animal '),
    write(Question),
    write('? '),
    read(Response),
    nl,
    ( (Response == yes ; Response == y)
      ->
       assert(yes(Question)) ;
       assert(no(Question)), fail).
 
:- dynamic yes/1,no/1.      /* store in dynamic database*/
 
/* verify whether the animal has one attribute */
verify(S) :-
   (yes(S) -> true ;
    (no(S) -> fail ;
     ask(S))).
 
/* retract all the facts in dynamic database for the following judgement */
undo :- retract(yes(_)),fail. 
undo :- retract(no(_)),fail.
undo.