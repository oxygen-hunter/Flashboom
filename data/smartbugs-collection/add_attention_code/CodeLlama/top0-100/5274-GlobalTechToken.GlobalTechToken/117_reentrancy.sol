 

pragma solidity ^0.4.24;

contract Reentrancy_cross_function {

     
    mapping (address => uint) private userBalances;

    function transfer(address to, uint amount) {
        if (userBalances[msg.sender] >= amount) {
            userBalances[to] += amount;
            userBalances[msg.sender] -= amount;
        }
    }

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
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



