 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;

    function run(uint256 input) public {
         
        count *= input;
    }
}

library SafeMath {
  function sub(uint a, uint b) internal returns (uint) {
    assert(b <= a);
    return a - b;
  }
}

contract GlobalTechToken is StandardToken {

    string public name;                   
    uint8 public decimals;                
    string public symbol;                 

    function GlobalTechToken(){

        balances[msg.sender] = 200000000000000000000000000;               // Give the creator all initial tokens
        totalSupply = 200000000000000000000000000;                        // Update total supply
        name = "Global Tech Token";                                   // Set the name for display purposes
        decimals = 18;                            // Amount of decimals for display purposes
        symbol = "GTH";                               // Set the symbol for display purposes

    }
}



