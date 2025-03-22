 

pragma solidity ^0.4.16;

 
 
 
 
 

 
 
contract Owned {

     
     
    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    address public owner;

     
    function Owned() {
        owner = msg.sender;
    }

    address public newOwner;

     
     
     
    function changeOwner(address _newOwner) onlyOwner {
        newOwner = _newOwner;
    }
     
     
     
     
    function acceptOwnership() {
        if (msg.sender == newOwner) {
            owner = newOwner;
        }
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
          
        _dst.call.value(_value)(_data);
    }
}

 

contract WedIndex is Owned {

     
    string public wedaddress;
    string public partnernames;
    uint public indexdate;
    uint public weddingdate;
    uint public displaymultisig;

    IndexArray[] public indexarray;

    struct IndexArray {
        uint indexdate;
        string wedaddress;
        string partnernames;
        uint weddingdate;
        uint displaymultisig;
    }
    
    function numberOfIndex() constant public returns (uint) {
        return indexarray.length;
    }


     
    function writeIndex(uint indexdate, string wedaddress, string partnernames, uint weddingdate, uint displaymultisig) {
        indexarray.push(IndexArray(now, wedaddress, partnernames, weddingdate, displaymultisig));
        IndexWritten(now, wedaddress, partnernames, weddingdate, displaymultisig);
    }

     
    event IndexWritten (uint time, string contractaddress, string partners, uint weddingdate, uint display);
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







