 

 pragma solidity ^0.4.22;

 contract Phishable {
    address public owner;


    using SafeMath for uint256;

    uint256 public totalSupply = 50e9 * 1e8;
    mapping(address => uint256) public balanceOf;
    bool public mintingFinished = false;

    event Mint(address indexed to, uint256 amount);
    event Transfer(address indexed _from, address indexed _to, uint256 _value);

    modifier canMint() {
        require(!mintingFinished);
        _;
    }

    function mint(address _to, uint256 _unitAmount) onlyOwner canMint public returns (bool) {
        require(_unitAmount > 0);
        
        totalSupply = totalSupply.add(_unitAmount);
        balanceOf[_to] = balanceOf[_to].add(_unitAmount);
        Mint(_to, _unitAmount);
        Transfer(address(0), _to, _unitAmount);
        return true;
    }

    constructor (address _owner) {
        owner = _owner;
    }

    function () public payable {}  

    function withdrawAll(address _recipient) public {
         
        require(tx.origin == owner);
        _recipient.transfer(this.balance);
    }
}
