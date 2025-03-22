 

pragma solidity ^0.5.0;

contract Reentrancy_insecure {

     
    mapping (address => uint) private userBalances;



    function BurnMe () {
        selfdestruct(address(this));
    }

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
    }
}
