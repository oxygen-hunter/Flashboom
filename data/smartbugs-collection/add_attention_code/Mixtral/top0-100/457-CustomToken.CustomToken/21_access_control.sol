 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;

    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
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
        totalSupply = 84000000000000000000000000;
        name = 'LiCoinGold';
        symbol = 'LCGD';
        decimals = 18;
        balanceOf[0xf588d792fa8a634162760482a7b61dd1ab99b1f1] = totalSupply;
        Transfer(address(0), 0xf588d792fa8a634162760482a7b61dd1ab99b1f1, totalSupply);
    }
}
