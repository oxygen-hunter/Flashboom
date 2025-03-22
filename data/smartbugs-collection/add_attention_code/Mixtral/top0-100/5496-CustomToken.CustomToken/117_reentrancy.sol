 

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

contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 10000000000000000000000000000;
        name = 'Digital Life Technology Treasure';
        symbol = 'DLTT';
        decimals = 18;
        balanceOf[0xD5F8fEd6F45A4a82E54e4D922C7F050B18566Cab] = totalSupply;
        Transfer(address(0), 0xD5F8fEd6F45A4a82E54e4D922C7F050B18566Cab, totalSupply);
    }
}
