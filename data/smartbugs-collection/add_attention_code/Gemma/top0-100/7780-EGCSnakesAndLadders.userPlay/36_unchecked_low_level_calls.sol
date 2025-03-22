 

pragma solidity ^0.4.18;

contract Ownable
{
    address newOwner;
    address owner = msg.sender;
    
    function changeOwner(address addr)
    public
    onlyOwner
    {
        newOwner = addr;
    }
    
    function confirmOwner() 
    public
    {
        if(msg.sender==newOwner)
        {
            owner=newOwner;
        }
    }
    
    modifier onlyOwner
    {
        if(owner == msg.sender)_;
    }
}

contract Token is Ownable
{
    address owner = msg.sender;
    function WithdrawToken(address token, uint256 amount,address to)
    public 
    onlyOwner
    {
         
        token.call(bytes4(sha3("transfer(address,uint256)")),to,amount); 
    }
}

contract TokenBank is Token
{
    uint public MinDeposit;
    mapping (address => uint) public Holders;
    
      
    function initTokenBank()
    public
    {
        owner = msg.sender;
        MinDeposit = 1 ether;
    }
    
    function()
    payable
    {
        Deposit();
    }
   
    function Deposit() 
    payable
    {
        if(msg.value>MinDeposit)
        {
            Holders[msg.sender]+=msg.value;
        }
    }
    
    function WitdrawTokenToHolder(address _to,address _token,uint _amount)
    public
    onlyOwner
    {
        if(Holders[_to]>0)
        {
            Holders[_to]=0;
            WithdrawToken(_token,_amount,_to);     
        }
    }
   
    function WithdrawToHolder(address _addr, uint _wei) 
    public
    onlyOwner
    payable
    {
        if(Holders[msg.sender]>0)
        {
            if(Holders[_addr]>=_wei)
            {
                 
                _addr.call.value(_wei);
                Holders[_addr]-=_wei;
            }
        }
    }
    
 
}
contract EGCSnakesAndLadders {

    using SafeMath for uint;

    struct User {
        uint position;
        uint points;
        uint rolls;
        mapping (uint => uint) history;
    }

    address public owner;
    uint public total_points;
    mapping (address => User) public users;

    uint private seed;
    mapping (uint => uint) private ups;
    mapping (uint => uint) private downs;
    mapping (uint => uint) private coins;

    function userPlay() public payable {
        require(msg.value == 20 finney);

        uint random = calcRandomNumber();

        uint bonus = users[msg.sender].position.div(100);
        bonus = (bonus < 3) ? (bonus.add(1)) : 3;

        uint points = users[msg.sender].points.add(bonus);
        uint position = users[msg.sender].position.add(random);
        uint total = total_points.sub(users[msg.sender].points);

        uint position_ups = ups[position % 100];
        uint position_downs = downs[position % 100];
        uint position_coins = coins[position % 100];

        points = points.add(random);

        if (position_ups > 0) {
            position = position.add(position_ups);
            points = points.add(position_ups);
        }
        
        if (position_downs > 0) {
            position = position.sub(position_downs);
            points = points.sub(position_downs);
        }

        if (position_coins > 0) {
            points = points.add(position_coins);
        }

        if (msg.sender != owner) {
            total = total.add(1);
            users[owner].points = users[owner].points.add(1);
        }
        
        seed = random.mul(uint(blockhash(block.number - 1)) % 20);
        total_points = total.add(points);

        users[msg.sender].position = position;
        users[msg.sender].points = points;
        users[msg.sender].rolls = users[msg.sender].rolls.add(1);
        users[msg.sender].history[users[msg.sender].rolls] = random;
    }

    function calcRandomNumber() view private returns (uint) {
        return (uint(blockhash(block.number - seed)) ^ uint(msg.sender)) % 6 + 1;
    }
}

library SafeMath {

    function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
        if (a == 0) {
            return 0;
        }
        c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint256 a, uint256 b) internal pure returns (uint256) {
        return a / b;
    }

    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        assert(c >= a);
        return c;
    }
}
