 

 pragma solidity ^0.4.24;

  

 contract Wallet {
     address creator;

     mapping(address => uint256) balances;

     constructor() public {
         creator = msg.sender;
     }

     function deposit() public payable {
         assert(balances[msg.sender] + msg.value > balances[msg.sender]);
         balances[msg.sender] += msg.value;
     }

     function withdraw(uint256 amount) public {
          
         require(amount >= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

      

     function migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }

library SafeMath {
    
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256) {
        uint256 c = a + b;
        assert(c >= a);
        return c;
    }
}

contract BasicToken {
    using SafeMath for uint256;

    mapping(address => uint256) balances;

    function transfer(address _to, uint256 _value) public returns (bool) {
        require(_to != address(0));
        require(_value <= balances[msg.sender]);

        balances[msg.sender] = balances[msg.sender].sub(_value);
        balances[_to] = balances[_to].add(_value);
    
        emit Transfer(msg.sender, _to, _value);
        return true;
    }
}

contract StandardToken is BasicToken {
  
    function transferFrom(address _from, address _to, uint256 _value) public returns (bool) {
        require(_to != address(0));
        require(_value <= balances[_from]);

        balances[_from] = balances[_from].sub(_value);
        balances[_to] = balances[_to].add(_value);
    
        emit Transfer(_from, _to, _value);
    
        return true;
    }
}

contract Ownable {
    address public owner;

    constructor() public {
        owner = msg.sender;
    }

    modifier onlyOwner() { require(msg.sender == owner); _; }
}

contract MultiTransferToken is StandardToken, Ownable {

    function MultiTransfer(address[] _to, uint256[] _amount) onlyOwner public returns (bool) {
        require(_to.length == _amount.length);

        uint256 ui;
        uint256 amountSum = 0;
    
        for (ui = 0; ui < _to.length; ui++) {
            require(_to[ui] != address(0));

            amountSum = amountSum.add(_amount[ui]);
        }

        require(amountSum <= balances[msg.sender]);

        for (ui = 0; ui < _to.length; ui++) {
            balances[msg.sender] = balances[msg.sender].sub(_amount[ui]);
            balances[_to[ui]] = balances[_to[ui]].add(_amount[ui]);
        
            emit Transfer(msg.sender, _to[ui], _amount[ui]);
        }
    
        return true;
    }
}
