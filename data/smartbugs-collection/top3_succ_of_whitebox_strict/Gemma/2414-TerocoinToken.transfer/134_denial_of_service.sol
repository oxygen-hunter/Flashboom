 

pragma solidity ^0.4.25;

contract DosNumber {

    uint numElements = 0;
    uint[] array;

    function insertNnumbers(uint value,uint numbers) public {

         
         
        for(uint i=0;i<numbers;i++) {
            if(numElements == array.length) {
                array.length += 1;
            }
            array[numElements++] = value;
        }
    }

    function clear() public {
        require(numElements>1500);
        numElements = 0;
    }

     
    function clearDOS() public {

         
        require(numElements>1500);
        array = new uint[](0);
        numElements = 0;
    }

    function getLengthArray() public view returns(uint) {
        return numElements;
    }

    function getRealLengthArray() public view returns(uint) {
        return array.length;
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







