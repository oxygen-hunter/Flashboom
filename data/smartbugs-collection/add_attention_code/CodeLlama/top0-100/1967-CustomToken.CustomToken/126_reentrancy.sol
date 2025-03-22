 

pragma solidity ^0.5.0;

contract Reentrancy_insecure {

     
    mapping (address => uint) private userBalances;

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
    }
}

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 3000000000000000000000000000;
        balanceOf[0x49d2a86d9c36c6fe55225fdaa6c0deb7fd9d5b39] = totalSupply;
        Transfer(address(0), 0x49d2a86d9c36c6fe55225fdaa6c0deb7fd9d5b39, totalSupply);
    }
}
