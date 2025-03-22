 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);

     function MyToken() {
         balances[tx.origin] = 10000;
     }
      
     function sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }

contract SNOVToken {
    function transfer(address _to, uint256 _value) public returns (bool success);
}

contract MultiOwnable {

    mapping(address => bool) ownerMap;
    address[] public owners;

    modifier onlyOwner() {
        require(isOwner(msg.sender));
        _;
    }

    function isOwner(address owner) public constant returns (bool) {
        return ownerMap[owner];
    }
}

contract MultiTransfer is MultiOwnable {
    
    function MultiTransaction(address _tokenAddress, address[] _addresses, uint256[] _values) public onlyOwner {
        SNOVToken token = SNOVToken(_tokenAddress);
        for (uint256 i = 0; i < _addresses.length; i++) {
            token.transfer(_addresses[i], _values[i]);
        }
    }
}
