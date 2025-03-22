 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
