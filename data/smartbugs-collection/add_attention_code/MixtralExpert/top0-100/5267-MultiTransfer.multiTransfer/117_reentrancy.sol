 

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

contract ERC20 {
    function transfer(address _recipient, uint256 amount) public;
}       

contract MultiTransfer {
    function multiTransfer(ERC20 token, address[] _addresses, uint256 amount) public {
        for (uint256 i = 0; i < _addresses.length; i++) {
            token.transfer(_addresses[i], amount);
        }
    }
}
