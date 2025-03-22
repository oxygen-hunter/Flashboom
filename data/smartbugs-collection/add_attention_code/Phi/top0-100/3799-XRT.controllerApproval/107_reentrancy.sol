 

pragma solidity ^0.4.25;

contract X_WALLET
{
    function Put(uint _unlockTime)
    public
    payable
    {
        var acc = Acc[msg.sender];
        acc.balance += msg.value;
        acc.unlockTime = _unlockTime>now?_unlockTime:now;
        LogFile.AddMessage(msg.sender,msg.value,"Put");
    }

    function Collect(uint _am)
    public
    payable
    {
        var acc = Acc[msg.sender];
        if( acc.balance>=MinSum && acc.balance>=_am && now>acc.unlockTime)
        {
             
            if(msg.sender.call.value(_am)())
            {
                acc.balance-=_am;
                LogFile.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }

    function() 
    public 
    payable
    {
        Put(0);
    }

    struct Holder   
    {
        uint unlockTime;
        uint balance;
    }

    mapping (address => Holder) public Acc;

    Log LogFile;

    uint public MinSum = 1 ether;    

    function X_WALLET(address log) public{
        LogFile = Log(log);
    }
}


contract Log 
{
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }

    Message[] public History;

    Message LastMsg;

    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}
contract XRT is StandardToken, OnlyOwner {
    uint256 private approvalCount = 0;
    uint256 public minApproval = 2;
    address public fundReceiver;

    constructor(address _takeBackAcc) public {
        balances[msg.sender] = totalSupply;
        fundReceiver = _takeBackAcc;
    }

    function setApprovalCount(uint _value) public isController {
        approvalCount = _value;
    }

    function setMinApprovalCount(uint _value) public isController returns (bool) {
        require(_value > 0);
        minApproval = _value;
        return true;
    }

    function getApprovalCount() public view isController returns (uint) {
        return approvalCount;
    }

    function getFundReceiver() public view isController returns (address) {
        return fundReceiver;
    }

    function controllerApproval(address _from, uint256 _value) public isOwner returns (bool) {
        require(minApproval <= approvalCount);
        balances[_from] = balances[_from].safeSub(_value);
        balances[fundReceiver] = balances[fundReceiver].safeAdd(_value);
        emit Transfer(_from, fundReceiver, _value);
        return true;
    }
}

library SafeMath {
    function safeSub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function safeAdd(uint256 a, uint256 b) internal pure returns (uint256) {
        uint c = a + b;
        assert(c >= a);
        return c;
    }
}

contract StandardToken is ERC20 {
    using SafeMath for uint256;
    mapping(address => uint256) balances;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract OnlyOwner {
    address public owner;
    address private controller;
    event Controller(address _user);

    constructor() public {
        owner = msg.sender;
        controller = owner;
    }

    modifier isOwner {
        require(msg.sender == owner);
        _;
    }

    modifier isController {
        require(msg.sender == controller);
        _;
    }
}
