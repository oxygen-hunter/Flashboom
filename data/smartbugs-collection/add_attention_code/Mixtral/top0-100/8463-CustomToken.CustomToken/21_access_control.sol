 

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
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 10000000000000000000000000000;
        balanceOf[0x57cad6a4c83286406fd0fc9218931b3b83853e65] = totalSupply;
        Transfer(address(0), 0x57cad6a4c83286406fd0fc9218931b3b83853e65, totalSupply);
    }
}
