// logger.h
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <mutex>

struct tm;

namespace logger
{
	// ǿ����ö�٣�ָ����־�ȼ�
	enum class Level { Debug, Info, Warning, Error, Fatal };
	class FileLogger; // д�ĵ��õ���־��
	class ConsoleLogger; // ����̨����õ���־��
	class BaseLogger; // �������

	class BaseLogger
	{
		class LogStream; // �����ı�������ڲ�������
	public:
		BaseLogger() = default;
		virtual ~BaseLogger() = default;
		// ���� operator() ���ػ���������
		virtual LogStream operator()(Level nLevel = Level::Debug);
	private:
		const tm* getLocalTime();
		// ����������������ʱ���ã�����������֤�̰߳�ȫ��
		void endline(Level nLevel, std::string&& oMessage);
		// ���麯����Ԥ���ӿڣ���������ʵ��
		virtual void output(const tm* p_tm,
			const char* str_level,
			const char* str_message) = 0;
	private:
		std::mutex _lock;
		tm _localTime;
	};

	// �����ı����������࣬�̳� std::ostringstream
	class BaseLogger::LogStream : public std::ostringstream
	{
		BaseLogger& m_oLogger;
		Level        m_nLevel;
	public:
		LogStream(BaseLogger& oLogger, Level nLevel)
			: m_oLogger(oLogger), m_nLevel(nLevel) {};
		LogStream(const LogStream& ls)
			: m_oLogger(ls.m_oLogger), m_nLevel(ls.m_nLevel) {};
		~LogStream() // Ϊ����д����������������ʱ����־
		{
			m_oLogger.endline(m_nLevel, std::move(str()));
		}
	};

	// ����̨����õ���־��
	class ConsoleLogger : public BaseLogger
	{
		using BaseLogger::BaseLogger;
		virtual void output(const tm* p_tm,
			const char* str_level,
			const char* str_message);
	};

	// д�ĵ��õ���־��
	class FileLogger : public BaseLogger
	{
	public:
		FileLogger(std::string filename) noexcept;
		FileLogger(const FileLogger&) = delete;
		FileLogger(FileLogger&&) = delete;
		virtual ~FileLogger();
	private:
		virtual void output(const tm* p_tm,
			const char* str_level,
			const char* str_message);
	private:
		std::ofstream _file;
	};

	extern ConsoleLogger debug;
	extern FileLogger record;

} // namespace logger
