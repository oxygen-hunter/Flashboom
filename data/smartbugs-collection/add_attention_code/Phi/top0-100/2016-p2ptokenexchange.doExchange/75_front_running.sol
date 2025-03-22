 

pragma solidity ^0.4.24;

 
library SafeMath {

   
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
     
     
     
    if (a == 0) {
      return 0;
    }

    uint256 c = a * b;
    require(c / a == b);

    return c;
  }

   
  function div(uint256 a, uint256 b) internal pure returns (uint256) {
    require(b > 0);  
    uint256 c = a / b;
     

    return c;
  }

   
  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    require(b <= a);
    uint256 c = a - b;

    return c;
  }

   
  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    require(c >= a);

    return c;
  }

   
  function mod(uint256 a, uint256 b) internal pure returns (uint256) {
    require(b != 0);
    return a % b;
  }
}


contract ERC20 {

  event Transfer( address indexed from, address indexed to, uint256 value );
  event Approval( address indexed owner, address indexed spender, uint256 value);
  using SafeMath for *;

  mapping (address => uint256) private _balances;

  mapping (address => mapping (address => uint256)) private _allowed;

  uint256 private _totalSupply;

  constructor(uint totalSupply){
    _balances[msg.sender] = totalSupply;
  }

  function balanceOf(address owner) public view returns (uint256) {
    return _balances[owner];
  }


  function allowance(address owner, address spender) public view returns (uint256)
  {
    return _allowed[owner][spender];
  }

  function transfer(address to, uint256 value) public returns (bool) {
    require(value <= _balances[msg.sender]);
    require(to != address(0));

    _balances[msg.sender] = _balances[msg.sender].sub(value);
    _balances[to] = _balances[to].add(value);
    emit Transfer(msg.sender, to, value);
    return true;
  }
   
  function approve(address spender, uint256 value) public returns (bool) {
    require(spender != address(0));
      
    _allowed[msg.sender][spender] = value;
    emit Approval(msg.sender, spender, value);
    return true;
  }

  function transferFrom(address from, address to, uint256 value) public returns (bool) {
    require(value <= _balances[from]);
    require(value <= _allowed[from][msg.sender]);
    require(to != address(0));

    _balances[from] = _balances[from].sub(value);
    _balances[to] = _balances[to].add(value);
    _allowed[from][msg.sender] = _allowed[from][msg.sender].sub(value);
    emit Transfer(from, to, value);
    return true;
  }
}
pragma solidity ^0.4.24;

contract TCallee {
    function transferFrom(address _from, address _to, uint256 _value) external returns (bool success) {}
}

contract p2ptokenexchange {
    
    struct exchange {
        address one1;
        address smart1;
        uint256 amount1;
        address two2;
        address smart2;
        uint256 amount2;
        bool DealDone;
    }
    
    mapping (uint => exchange) exchanges;
    address constant atokenaddress = 0xf0B3BA2Dd4B2ef75d727A4045d7fBcc415B77bF0;
    event DoExchange (uint exchangeId);
    
    function doExchange (uint exchangeId) external payable returns (bool success) {
        bool _locked;
        require(!_locked);
        _locked = true;
        require(msg.value >= 206000000);
        if (exchanges[exchangeId].two2 != 0x1111111111111111111111111111111111111111) {
            require(msg.sender == exchanges[exchangeId].two2);
        } else {
            exchanges[exchangeId].two2 = msg.sender;
        }
   
        require(exchanges[exchangeId].DealDone == false);
        require(exchanges[exchangeId].amount2 > 0);
       
        if (exchanges[exchangeId].smart2 == address(0)) {
            require(msg.value >= 206000000 + exchanges[exchangeId].amount2);
            require(payether(atokenaddress, msg.value - exchanges[exchangeId].amount2) == true);
        } else {
            require(payether(atokenaddress, msg.value) == true);
        }

        if (exchanges[exchangeId].smart2 == address(0)) {
            require(payether(exchanges[exchangeId].one1, exchanges[exchangeId].amount2) == true);
        } else {
            TCallee c = TCallee(exchanges[exchangeId].smart2);
            bool x = c.transferFrom(exchanges[exchangeId].two2, exchanges[exchangeId].one1, exchanges[exchangeId].amount2);
            require(x == true);
        }

        if (exchanges[exchangeId].smart1 == address(0)) {
            require(payether(exchanges[exchangeId].two2, exchanges[exchangeId].amount1) == true);
        } else {
            TCallee d = TCallee(exchanges[exchangeId].smart1);
            bool y = d.transferFrom(exchanges[exchangeId].one1, exchanges[exchangeId].two2, exchanges[exchangeId].amount1);
            require(y == true);
        }
        
        exchanges[exchangeId].DealDone = true;
        emit DoExchange(exchangeId);
        _locked = false;
        return true;
    }

    function payether(address payto, uint256 amountTo) internal returns (bool) {
        payto.transfer(amountTo);
        return true;
    }
}
