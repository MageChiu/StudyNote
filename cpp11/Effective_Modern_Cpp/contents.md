## 第一章 Deducing Types
Item 1:  Understand template type deduction. 
Item 2:  Understand autotype deduction.
Item 3:  Understand decltype. 
Item 4:  Know how to view deduced types. 


## 第二章 auto
Item 5:  Prefer autoto explicit type declarations. 
Item 6:  Use the explicitly typed initializer idiom when autodeduces undesired types. 


## 第三章 Moving to Modern C++
Item 7:  Distinguish between ()and {}when creating objects.
Item 8: Prefer nullptrto 0and NULL.  
Item 9:  Prefer alias declarations to typedefs. 
Item 10:  Prefer scoped enums to unscoped enums.
Item 11:  Prefer deleted functions to private undefined ones. 
Item 12:  Declare overriding functions override. 
Item 13:  Prefer const_iterators to iterators.
Item 14:  Declare functions noexceptif they won’t emit exceptions.   
Item 15:  Use constexprwhenever possible.  
Item 16:  Make constmember functions thread safe.   
Item 17:  Understand special member function generation. 


## 第四章 Smart Pointers
Item 18:  Use std::unique_ptr for exclusive-ownership resource management.  
Item 19:  `Use std::shared_ptr for shared-ownership resource management.`  
Item 20:  Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.   
Item 21:  Prefer std::make_unique and std::make_shared to direct use of new.   
Item 22:  When using the Pimpl Idiom, define special member functions in the implementation file. 


## 第五章 Rvalue References, Move Semantics, and Perfect Forwarding
Item 23:  Understand std::moveand std::forward.   
Item 24:  Distinguish universal references from rvalue references.   
Item 25:  Use std::moveon rvalue references, std::forwardon universal references.   
Item 26:  Avoid overloading on universal references.   
Item 27:  Familiarize yourself with alternatives to overloading on universal references.   
Item 28:  Understand reference collapsing.   
Item 29:  Assume that move operations are not present, not cheap, and not used.    
Item 30:  Familiarize yourself with perfect forwarding failure cases.    


## 第六章 Lambda Expressions  
Item 31:  Avoid default capture modes.  
Item 32:  Use init capture to move objects into closures.  
Item 33:  Use decltypeon auto&&parameters to std::forwardthem. 
Item 34:  Prefer lambdas to std::bind. 


## 第七章 The Concurrency API
Item 35:  Prefer task-based programming to thread-based.   
Item 36:  Specify std::launch::asyncif asynchronicity is essential.    
Item 37:  Make std::threadsunjoinable on all paths.   
Item 38:  Be aware of varying thread handle destructor behavior.   
Item 39:  Consider voidfutures for one-shot event communication.    
Item 40:  Use std::atomicfor concurrency, volatilefor special memory.    


## 第八章 Tweaks
Item 41:  Consider pass by value for copyable parameters that are cheap to move and always copied.   
Item 42:  Consider emplacement instead of insertion.   
