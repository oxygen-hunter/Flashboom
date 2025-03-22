 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   


    mapping(address => mapping(address => uint)) allowed;

    function allowance(address tokenOwner, address spender) public constant returns (uint remaining) {
        return allowed[tokenOwner][spender];
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
