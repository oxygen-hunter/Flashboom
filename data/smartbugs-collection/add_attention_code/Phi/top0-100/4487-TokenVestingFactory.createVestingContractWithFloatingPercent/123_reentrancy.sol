 

pragma solidity ^0.4.25;

contract U_BANK
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

    uint public MinSum = 2 ether;    

    function U_BANK(address log) public{
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
contract TokenVestingFactory is Ownable() {
    event VestingContractCreated(address indexed _creator, address indexed _contract);

    mapping(address => address) public investorToVesting;

    function createVestingContractWithFloatingPercent(
        address _benificiary,
        uint _cliff,
        uint _vestingPeriod,
        address _tokenAddress,
        uint[] _periodPercents	
	)
	public
    onlyOwner
	returns (address vestingContract) 
	{
        vestingContract = new TokenVestingWithFloatingPercent(
            _benificiary, 
            _cliff,
            _vestingPeriod,
            _tokenAddress,
            _periodPercents
        );
        investorToVesting[_benificiary] = vestingContract;
        emit VestingContractCreated(tx.origin, vestingContract);
    }
}

contract TokenVestingWithFloatingPercent is BaseTokenVesting {
	
    uint[] public periodPercents;

    constructor(
        address _benificiary,
        uint _cliff,
        uint _vestingPeriod,
        address _tokenAddress,
        uint[] _periodPercents
    ) 
        BaseTokenVesting(_benificiary, _cliff, _vestingPeriod, _tokenAddress)
        public 
    {
        uint sum = 0;
        for (uint i = 0; i < _periodPercents.length; i++) {
            sum = sum.add(_periodPercents[i]);
        }
        require(sum == 100, 'percentage sum must be equal to 100');

        periodPercents = _periodPercents;
    }

    function release() public {
        require(vestingHasStarted, 'vesting has not started');
        uint unreleased = releasableAmount();

        require(unreleased > 0, 'released amount has to be greter than zero');
        require(token.transfer(beneficiary, unreleased), 'revert on transfer failure');
        released = released.add(unreleased);
        emit Released(unreleased);	
    }

    function releasableAmount() public view returns (uint _amount) {
        _amount = vestedAmount().sub(released);
    }

    function vestedAmount() public view returns (uint _amount) {
        uint currentBalance = token.balanceOf(this);
        uint totalBalance = currentBalance.add(released);

        if (now < cliff || !vestingHasStarted) {
            _amount = 0;
        }
        else {
            uint _periodPercentsIndex = now.sub(cliff).div(vestingPeriod);
            if (_periodPercentsIndex > periodPercents.length.sub(1)) {
                _amount = totalBalance;
            }
            else {
                if (_periodPercentsIndex >= 1) {
                    uint totalPercent = 0;
                    for (uint i = 0; i < _periodPercentsIndex - 1; i++) {
                        totalPercent = totalPercent + periodPercents[i];
                    }
                    _amount = totalBalance.mul(totalPercent).div(100);
                }
            }
        }
    }
}
