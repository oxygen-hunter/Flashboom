 

pragma solidity ^0.5.0;

contract Reentrancy_insecure {

     
    mapping (address => uint) private userBalances;


    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
    }
}
