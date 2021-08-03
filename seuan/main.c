// header
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

// define
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

int	ft_strlen(char *str)
{
	int			len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}


// philosopher 구조체

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct s_info
{   
    int num_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int must_eating;
    int init_time;
    int dead;
    pthread_mutex_t status;
    pthread_mutex_t *fork;
    t_philo *philo;
};

struct s_philo
{
    int id;
    int stt;
    int fork_l;
    int fork_r;
    t_info *info;
    pthread_t thread;
    pthread_t monitor;
    pthread_mutex_t philo_lock;
};

int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    init_info(t_info *info, char **argv)
{
    info->num_philo = ft_atoi(argv[1]);
    info->time_die = ft_atoi(argv[2]);
    info->time_eat = ft_atoi(argv[3]);
    info->time_sleep = ft_atoi(argv[4]);
    info->dead = 0;
    info->init_time = 0;
    if (argv[5])
        info->must_eating = ft_atoi(argv[5]);
    pthread_mutex_init(&info->status, NULL);
}

void    init_fork(t_info *info)
{
    int i;

    info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_philo);
    i = 0;
    while (i < info->num_philo)
    {
        pthread_mutex_init(&info->fork[i], NULL);
        i++;
    }
}

void    init_philo(t_info *info)
{
    int i;

    info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
    i = 0;
    while (i < info->num_philo)
    {
        info->philo[i].id = i;
        info->philo[i].info = info;
        info->philo[i].stt = 0;
        info->philo[i].fork_l = i;
        info->philo[i].fork_r = (i + 1) % info->num_philo;
        pthread_mutex_init(&info->philo[i].philo_lock, NULL);
        i++;
    }
}

void    print_status(t_philo *philo, int status)
{
    // Befort print, mutex lock thread
    pthread_mutex_lock(&philo->info->status);
    if (philo->info->dead)
    {
        pthread_mutex_unlock(&philo->info->status);
        return;
    }

    // timestamp in ms
    printf("[%dms] ", current_time() - philo->info->init_time);

    // thread num
    printf("%d philosopher ", philo->id + 1);
    
    // msg
    if (status == FORK)
        printf("has taken a fork\n");
    else if (status == EAT)
        printf("is eating\n");
    else if (status == SLEEP)    
        printf("is sleeping\n");
    else if (status == THINK)
        printf("is thinking\n");
    else if (status == DIE)
        printf("died\n");
    pthread_mutex_unlock(&philo->info->status);
}

void *philosopher(void *arg)
{
    int sleep_time;
    t_philo *philo;

    // thread 생성 시 넘어오는 매개변수 받기
    philo = arg;

    // 짝수 thread에 대해 usleep을 지정함으로써 홀수 thread가 우선적으로 실행되게 함.
    if (philo->id % 2 == 0)
        usleep(1000 * philo->info->time_eat);

    // thread가 실행되는 가상의 시간 설정
    while (!philo->info->dead)
    {
        pthread_mutex_lock(&philo->info->fork[philo->fork_r]);
        print_status(philo, FORK);
        pthread_mutex_lock(&philo->info->fork[philo->fork_l]);
        print_status(philo, FORK);
        pthread_mutex_lock(&philo->philo_lock);
        print_status(philo, EAT);
        pthread_mutex_unlock(&philo->philo_lock);
        while (current_time() - philo->stt <= philo->info->time_eat && !philo->info->dead)
            usleep(1000);
        philo->stt = current_time();
        pthread_mutex_unlock(&philo->info->fork[philo->fork_r]);
        pthread_mutex_unlock(&philo->info->fork[philo->fork_l]);
        sleep_time = current_time();
        print_status(philo, SLEEP);
        while(current_time() - sleep_time <= philo->info->time_sleep && !philo->info->dead)
            usleep(1000);
        print_status(philo, THINK);
    }
    return NULL;
}

void    *monitor(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (!philo->info->dead)
    {
        pthread_mutex_lock(&philo->philo_lock);
        if (current_time() - philo->stt >= philo->info->time_die)
        {
            philo->info->dead = 1;
            print_status(philo, DIE);
            pthread_mutex_unlock(&philo->philo_lock);
            break;
        }
        pthread_mutex_unlock(&philo->philo_lock);
        usleep(100);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int i = 0;
    t_info info;

    // 올바른 인자 수 여부 체크.
    if (!(argc == 5 || argc == 6))
        return (0);
    init_info(&info, argv);

    // mutex init fork
    init_fork(&info);

    // init philo
    init_philo(&info);

    // pthread_create thread
    info.init_time = current_time();
    i = 0;
    while (i < info.num_philo)
    {
        info.philo[i].stt = current_time();
        if (pthread_create(&(info.philo[i].thread), NULL, &philosopher, &info.philo[i]))
            return (printf("Failed create thread\n"));
        if (pthread_create(&(info.philo[i].monitor), NULL, &monitor, &info.philo[i]))
            return (printf("Failed create thread\n"));
        // usleep(100);
        i++;
    } 
    // pthread_join
    i = 0;
    while (i < info.num_philo)
    {
        if (pthread_join(info.philo[i].thread, NULL))
            return (printf("Failed to join thread.\n"));
        if (pthread_join(info.philo[i].monitor, NULL))
            return (printf("Failed to join thread.\n"));
        i++;
    }
    return 0;
}